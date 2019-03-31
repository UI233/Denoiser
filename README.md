# Denoiser
A command line mesh denoiser
This project is built by CMake
### Dependencies
OpenMesh library

### How to use it?
usage:
  denoiser <type of denoiser> <path to the model> <noise level> [parameters for denoiser]

  if some of [parameters for denoiser] is lost, those parameters would be set to default parameters.

| command | types of denoiser                              |
| ------- | ---------------------------------------------- |
| 0       | BilateralMeshDenoising                         |
| 1       | BilateralNormalFiltering                       |
| 2       | FastAndEffectiveFeaturePreservingMeshDenoising |
| 3       | MeshDenoisingViaL0Minimization                 |
| 4       | NonIterativeFeaturePreservingMeshFiltering     |

For example:

./denoiser.exe 0 blade.norm.obj 0.3 20

The program would add noises of 0.3 noise level to the model and then applies BilateralMeshDenoising to the noisy model with 20 iterations.

Then the program would export the noisy and denoised models.

