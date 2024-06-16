# GameEngineSandbox

![Azure pipeline badge](https://coderox.visualstudio.com/Game%20Engine%20Sandbox/_apis/build/status/Build%20master%20branch)
[![CodeFactor](https://www.codefactor.io/repository/github/johanlindfors/gameenginesandbox/badge)](https://www.codefactor.io/repository/github/johanlindfors/gameenginesandbox)
[![CodeQL](https://github.com/johanlindfors/GameEngineSandbox/actions/workflows/codeql-analysis.yml/badge.svg)](https://github.com/johanlindfors/GameEngineSandbox/actions/workflows/codeql-analysis.yml)

To try this small game engine follow these steps:
```
git clone https://github.com/johanlindfors/GameEngineSandbox.git
```

Make sure to fetch the thirdparty submodules:
```
git submodule update --init
```

These two commands can be combined as follows:
```
git clone --recurse-submodules https://github.com/johanlindfors/GameEngineSandbox.git
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

## Building on Linux or MacOS
Make sure to install the following:
```
sudo apt install libpng-dev pkg-config libglfw3-dev libssl-dev libjpeg-dev
```

Generate all the files needed to build the application, build and run:
```
cd build
cmake ..
cmake --build .
./games/sokoban/sokoban
```

## Building for HTML5/WASM
First you need to install and configure the Emscripten SDK. The GitHub repository can be found here: https://github.com/emscripten-core/emsdk

After properly configured the SDK, you can follow the script above with some minor tweaks as follows:
```
cd build
emcmake cmake ..
emmake make --build .
emrun ./games/sokoban
```

If it's the first time you build anything with emscripten you can (or at least I did) stumble upon some missing headers (usually png.h). In that case you need to leverage the emscripten compiler (emcc) and pass the following parameter ```-sUSE_LIBPNG```. This will make sure to download the LIBPNG port and any dependencies and place it in the appopriate directory (on my machines it was in the emsdk repository under ```upstream/emscripten/cache/ports```.

What I did was I created a simple c++ sample and then called the following command:

```
emcc sample.cpp -sUSE_LIBPNG
```

There are three small games that can be build by passing the name as an argument to CMake such as:

```
cmake .. -DGAME_TO_BUILD=snake
```
or
```
cmake .. -DGAME_TO_BUILD=flappybird
```
or
```
cmake .. -DGAME_TO_BUILD=sokoban
```

There is also a simple sample that demonstrates the 3D capabilities with a ModelRenderer
```
cmake .. -DGAME_TO_BUILD=sample
```

Here are some screenshots of the current state of the applications/games:


<img src="https://raw.githubusercontent.com/johanlindfors/GameEngineSandbox/main/docs/flappybird_screenshot.png" height="200"/>


<img src="https://raw.githubusercontent.com/johanlindfors/GameEngineSandbox/main/docs/snake_screenshot.png" height="200"/>


<img src="https://raw.githubusercontent.com/johanlindfors/GameEngineSandbox/main/docs/sokoban_screenshot.png" height="200"/>


<img src="https://raw.githubusercontent.com/johanlindfors/GameEngineSandbox/main/docs/sample_screenshot1.png" height="200"/>


<img src="https://raw.githubusercontent.com/johanlindfors/GameEngineSandbox/main/docs/sample_screenshot2.png" height="200"/>

Game on!
