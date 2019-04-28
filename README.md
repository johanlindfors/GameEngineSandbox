# GameEngineSandbox

![Azure pipeline badge](https://coderox.visualstudio.com/Game%20Engine%20Sandbox/_apis/build/status/Build%20master%20branch)

git clone https://github.com/coderox/GameEngineSandbox.git

Make sure to fetch the thirdparty submodules:

  git submodule init
  git submodule update

If you want to build Win32 version, make sure to bootstrap vcpkg and fetch Win32 specific dependencies
./dependencies/thirdparty/vcpkg/bootstrap-vcpkg.bat
./dependencies/thirdparty/vcpkg/vcpkg.exe install glew:x64-windows
./dependencies/thirdparty/vcpkg/vcpkg.exe install libpng:x64-windows
./dependencies/thirdparty/vcpkg/vcpkg.exe install opengl:x64-windows

The you can leverage the pipeline.ps1 Powershell command.

Here are a couple of examples:

Generate and build a release version for Universal Windows Platform
pipeline.ps1 -uwp -build

Only generate a debug version for Win32
pipeline.ps1 -win32 -debug -generate

Compile an already existing debug configuration for Win32
pipeline.ps1 -win32 -debug -compile

Generate and build a release version of Win32, leveraging an already installed vcpkg-toolchain
pipeline.ps1 -win32 -build -toolchainFile:[path to explicit toolchain file for vcpkg]
