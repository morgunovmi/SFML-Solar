# SFML-Solar 

## Introduction

A little game demo where you can see a fully simulated solar system evolve. Written with SFML and imgui.
![sc](https://user-images.githubusercontent.com/48750724/169697119-a6040a4a-0404-4fff-a244-2216b08ecb02.png)


## Playing

If you just want to play the game, you can download it on the Releases page of this repo.

## Build

These build instructions are for a release build and assume you have CMake installed, have vcpkg in path-to-vcpkg.
Steps for Windows(x64):

```
git clone https://github.com/morgunovmi/SFML-Solar.git
cd SFML-Solar
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=path-to-vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-windows ..
cmake --build . --config=Release
..\bin\Release\Release\SolarApp.exe
```

Steps for Linux(x64):

```
git clone https://github.com/morgunovmi/SFML-Solar.git
cd SFML-Solar
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DCMAKE_TOOLCHAIN_FILE=path-to-vcpkg\scripts\buildsystems\vcpkg.cmake -DVCPKG_TARGET_TRIPLET=x64-linux ..
cmake --build .
..\bin\Release\SolarApp.exe
```
