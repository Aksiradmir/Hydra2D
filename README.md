Hydra2D
==============================================================

Implementation of the 2D [Smoothed-Particle Hydrodynamics (SPH)](https://en.wikipedia.org/wiki/Smoothed-particle_hydrodynamics) approach in the Fluid Dynamics simulations. 

You can find gifs of some examples [here](https://drive.google.com/drive/folders/14u24g3hSAFwDyopxVEmDRww0C6uSIaeM?usp=sharing).


Requirements
------------

- C++ (C++20 or newer)
- CMake (3.24 or newer)
- OpenMP (GCC already contains it)
- Numpy and Matplotlib for visualization using Python
- GraphicsMagick

Installation
------------

On Linux/macOS:
```bash
git clone https://github.com/Aksiradmir/Hydra2D.git
cd Hydra2D
mkdir build
cd build
cmake ..
make
./Hydra2D
```
