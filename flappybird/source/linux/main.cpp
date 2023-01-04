#include <iostream>
#include "game/Bootstrap.hpp"

void startLinuxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    bootstrap();

    startLinuxApplication(argc, argv);
  
    return 0;
}
