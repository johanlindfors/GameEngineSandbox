sudo apt install libpng-dev pkg-config libglfw3-dev
rm -fr build
mkdir build
cd build
cmake ..
cmake --build .