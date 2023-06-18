# GameEngineSandbox

![Azure pipeline badge](https://coderox.visualstudio.com/Game%20Engine%20Sandbox/_apis/build/status/Build%20master%20branch)
[![CodeFactor](https://www.codefactor.io/repository/github/johanlindfors/gameenginesandbox/badge)](https://www.codefactor.io/repository/github/johanlindfors/gameenginesandbox)
[![CodeQL](https://github.com/johanlindfors/GameEngineSandbox/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/johanlindfors/GameEngineSandbox/actions/workflows/codeql-analysis.yml)

To try this small game engine follow these steps:
```
git clone https://github.com/coderox/GameEngineSandbox.git
```

Make sure to fetch the thirdparty submodules:
```
git submodule update --init
```

## Building a Win32 version
If you want to build Win32 version, make sure to bootstrap vcpkg and fetch Win32 specific dependencies

```
./dependencies/thirdparty/vcpkg/bootstrap-vcpkg.bat
./dependencies/thirdparty/vcpkg/vcpkg.exe install glew:x64-windows
./dependencies/thirdparty/vcpkg/vcpkg.exe install libpng:x64-windows
./dependencies/thirdparty/vcpkg/vcpkg.exe install opengl:x64-windows
```

You can leverage the pipeline.ps1 Powershell command to automate the creation of the projects for your preferred platform.

#### Only generate a debug version for Win32
```
pipeline.ps1 -win32 -debug -generate
```

#### Compile an already existing debug configuration for Win32
```
pipeline.ps1 -win32 -debug -compile
```

#### Generate and build a release version of Win32, leveraging an already installed vcpkg-toolchain
```
pipeline.ps1 -win32 -build -toolchainFile:[path to explicit toolchain file for vcpkg]
```
### Building a UWP version
```
pipeline.ps1 -uwp -build
```

## Building on Ubuntu 22.04
Make sure to install the following:
```
sudo apt install libpng-dev pkg-config libglfw3-dev libssl-dev
```

Then in the root directory of this repository create a an output directory called build:
```
mkdir build
cd build
```

Generate all the files needed to build the application, build and run:
```
cmake ..
cmake --build .
./snake/snake
```

Game on!