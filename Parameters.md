### Choice for Parameters
In this experiment we would like to test the program using the parameters described below.

### Bilateral Normal Filter
param0(type of denoiser): 1

param1(path to the model): {all ".obj" within the directory}

param2(noise level): {0.005, 0.01, 0.05, 0.1, 0.2, 0.5, 0.7}

param3(global or local optimization):
{0, 1}

param4(common vertices or common edges): {0, 1}

param5(sigmac): {0.4, 0.5, 0.6, 0.65, 0.70, 0.75, 0.80, 0.9, 1.0}

param6(sigmas): {0.1, 0.2, 0.25, 0.3, 0.35, 0.4, 0.45, 0.5, 0.6}

param7(Iterations for normal filter): {1, 3, 5, 7, 10, 15, 20, 25}

param8(Smothness): If param3 is 0 then set it to an arbitary value otherwise the choice would be {0.5, 0.55, 0.6, 0.65, 0.70, 0.75, 0.80, 0.81, 0.82, 0.83, ..., 0.90, 0.95}

param9(Iterations of vertices filter): {x | 3 <=  x <= 15 and x is an integer}

### Fast And Effective Denoiser
param0(type of denoiser): 2

param1(path to the model): {all ".obj" within the directory}

param2(noise level): {0.005, 0.01, 0.05, 0.1, 0.2, 0.5, 0.7}

param3(common vertices or common edges): {0, 1}

param4(threshold): {0.05, 0.1, 0.15, 0.2, 0.3, 0.4, 0.45, 0.5, 0.6, 0.7, 0.8}

param5(Iterations num of normal filter): {1, 3, 5, 7, 10, 15, 20}

param6(Iterations num of vertices filter): {x | 3 <=  x <= 15 and x is an integer}