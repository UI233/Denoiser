#include "denoiser.h"
#include <string>
#include <vector>
#include <utility>
#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>

using std::string;
using std::vector;
using Error = std::pair<double, double>;

void addNoise(DataManager *data, double noise_level);
void denoise(DataManager *data, int argc, char *argv[]);
void process(int argc, char *argv[]);
Error estimateMSAE(DataManager &data);
template<typename T, typename U, class ...Types>
void setParameters(ParameterSet *param, T name, U value, Types... rest);
template<typename T, typename U>
void setParameters(ParameterSet *param, T name, U value);

int main(int argc, char *argv[])
{
    //QCoreApplication a(argc, argv);
    process(argc, argv);
    return 0;
}

template<typename T, typename U>
void setParameters(ParameterSet *param, T name, U value)
{
    param->setValue(name, value);
}

template<typename T, typename U, class ...Types>
void setParameters(ParameterSet *param, T name, U value, Types... rest)
{
    param->setValue(name, value);
    setParameters<T, U>(param, rest...);
}

Error estimateMSAE(DataManager &data)
{
    TriMesh original = data.getOriginalMesh();
    original.update_normals();
    TriMesh denoised_mesh = data.getDenoisedMesh();
    denoised_mesh.update_normals();
    TriMesh noisy_mesh = data.getNoisyMesh();
    noisy_mesh.update_normals();
    vector<TriMesh::Normal> original_normal, noisy_normal, denoised_normal;
    for(auto f_it = original.faces_begin(); f_it != original.faces_end(); f_it++)
    {
        TriMesh::Normal ni = original.normal(*f_it);
        original_normal.push_back(ni);
    }
    for(auto f_it = noisy_mesh.faces_begin(); f_it != noisy_mesh.faces_end(); f_it++)
    {
        TriMesh::Normal ni = noisy_mesh.normal(*f_it);
        noisy_normal.push_back(ni);
    }
    for(auto f_it = denoised_mesh.faces_begin(); f_it != denoised_mesh.faces_end(); f_it++)
    {
        TriMesh::Normal ni = denoised_mesh.normal(*f_it);
        denoised_normal.push_back(ni);
    }

    double noisy_error = 0.0, denoised_error = 0.0;
    for(decltype(original_normal.size()) sz = original_normal.size(), i = 0; i != sz; ++i)
    {
        denoised_error += acos(original_normal[i] | denoised_normal[i]);
        noisy_error += acos(original_normal[i] | noisy_normal[i]);
    }

    return Error(noisy_error / original_normal.size(), denoised_error / original_normal.size());
}


void process(int argc, char *argv[])
{
    auto model_name = string(argv[2]);
    model_name = model_name.substr(0, model_name.length() - 4);
    std::ofstream output(model_name + string(".out"), std::ios::app);
    DataManager data;
    ParameterSet param_denoiser;
    // Add noise to model and export it
    data.ImportMeshFromFile(argv[2]);
    addNoise(&data, std::stod(argv[3]));
    data.ExportMeshToFile(model_name + "(noisy " + argv[3]  + ").obj");
    // Denoise the model then measure the error and the duration
    auto beg = std::chrono::high_resolution_clock::now();
    denoise(&data, argc, argv);
    auto end = std::chrono::high_resolution_clock::now();

    auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg).count();
    auto er = estimateMSAE(data);
    // export the denoised model.
    data.ExportMeshToFile(model_name + "(" + argv[1] + argv[3]  + ").obj");
    output << er.first << " " << er.second <<  " " << duration << " " ;
    duration = std::chrono::duration_cast<std::chrono::milliseconds>(end - beg).count();
    output.close();
}

void addNoise(DataManager *data, double noise_level)
{
    ParameterSet param_noise;
    param_noise.setValue(string("Noise level"), noise_level);
    Noise noiser(data, &param_noise);
    noiser.addNoise();
    return ;
}

void denoise(DataManager *data, int argc, char *argv[])
{
    int denoiser_type = std::stoi(argv[1]);
    if(argc <= 3)
        return ;
    ParameterSet parameters;
    switch(denoiser_type){
    case 0:
    {
        BilateralMeshDenoising denoiser(data, &parameters);
        if(argc > 3)
            parameters.setValue("Iteration Num.", std::stod(argv[3]));
        denoiser.denoise();
    }
        break;
    case 1:
    {
        BilateralNormalFilteringForMeshDenoising denoiser(data, &parameters);
        if(argc > 3)
            parameters.setValue(string("sigma_s"), std::stod(argv[3]));
        if(argc > 4)
            parameters.setValue(string("Normal Iteration Num."), std::stoi(argv[4]));
        if(argc > 5)
            parameters.setValue(string("Smoothness"), std::stod(argv[5]));
        if(argc > 6)
            parameters.setValue(string("Vertex Iteration Num."), std::stoi(argv[6]));
        denoiser.denoise();
    }
        break;
    case 2:
    {
        FastAndEffectiveFeaturePreservingMeshDenoising denoiser(data, &parameters);
        if(argc > 3)
            parameters.setValue(string("Face Neighbor"), std::stoi(argv[3]));
        if(argc > 4)
            parameters.setValue(string("Threshold T"), std::stod(argv[4]));
        if(argc > 5)
            parameters.setValue(string("Normal Iteration Num."), std::stoi(argv[5]));
        if(argc > 6)
            parameters.setValue(string("Vertex Iteration Num."), std::stoi(argv[6]));
        denoiser.denoise();
    }
        break;
    case 4:
    {
        MeshDenoisingViaL0Minimization denoiser(data, &parameters);
        if(argc > 3)
           parameters.setValue(string("mu_beta"), std::stod(argv[3]));
        if(argc > 4)
            parameters.setValue(string("beta"), std::stod(argv[4]));
        if(argc > 5)
            parameters.setValue(string("beta_max"), std::stod(argv[5]));
        if(argc > 6)
            parameters.setValue(string("mu_alpha"), std::stod(argv[6]));
        denoiser.denoise();
    }
        break;
    case 5:
    {
        NonIterativeFeaturePreservingMeshFiltering denoiser(data, &parameters);
        if(argc > 3)
            parameters.setValue(string("sigma_f/mean_edge_length"), std::stod(argv[3]));
        if(argc > 4)
            parameters.setValue(string("sigma_g/mean_edge_length"), std::stod(argv[4]));
        denoiser.denoise();
    }
        break;
    }

}
