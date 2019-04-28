# GameEngineSandbox

![Azure pipeline badge](https://coderox.visualstudio.com/Game%20Engine%20Sandbox/_apis/build/status/Build%20master%20branch)

git clone https://github.com/coderox/GameEngineSandbox.git

git submodule init
git submodule update

./dependencies/thirdparty/vcpkg/bootstrap-vcpkg.bat
./dependencies/thirdparty/vcpkg/vcpkg.exe install glew:x64-windows
./dependencies/thirdparty/vcpkg/vcpkg.exe install libpng:x64-windows
./dependencies/thirdparty/vcpkg/vcpkg.exe install opengl:x64-windows

