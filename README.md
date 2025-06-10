# Particle Simulator

This repository contains a minimal 2D particle simulator using modern OpenGL.
The project is configured with CMake and intended to be used with Visual Studio 2022 on Windows 10.

## Building with vcpkg

1. Install [vcpkg](https://github.com/microsoft/vcpkg) and integrate it with Visual Studio (`vcpkg integrate install`).
2. From the repository root, run:

   ```
   vcpkg install --triplet x64-windows
   cmake -B build -S . -DCMAKE_TOOLCHAIN_FILE=[vcpkg-root]/scripts/buildsystems/vcpkg.cmake
   ```
   Replace `[vcpkg-root]` with the path to your vcpkg directory.
3. Open `build/ParticleSimulator.sln` in Visual Studio 2022 and build.

The required packages (`glad`, `glfw3`, `glm`) are declared in `vcpkg.json`.

## Running

After building, run the `particle_sim` executable. A window will appear with
particles bouncing within the view.
