sudo apt-get update
sudo apt install libpng-dev pkg-config libglfw3-dev libssl-dev libjpeg-dev libgles2-mesa-dev libxkbcommon-dev
# Build flappybird
rm -fr build
mkdir build
cd build
cmake .. -DGAME_TO_BUILD=flappybird
cmake --build .

# Build snake
cd ..
rm -fr build_snake
mkdir build_snake
cd build_snake
cmake .. -DGAME_TO_BUILD=snake
cmake --build .

# Build sample
cd ..
rm -fr build_sample
mkdir build_sample
cd build_sample
cmake .. -DGAME_TO_BUILD=sample
cmake --build .

# Build sokoban
cd ..
rm -fr build_sokoban
mkdir build_sokoban
cd build_sokoban
cmake .. -DGAME_TO_BUILD=sokoban -DUSE_HTTP=true
cmake --build .

# Build helloworld
cd ..
rm -fr build_helloworld
mkdir build_helloworld
cd build_helloworld
cmake .. -DGAME_TO_BUILD=helloworld
cmake --build .
