#include <iostream>
#include "game/Bootstrap.hpp"

void StartLinuxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    Bootstrap();

    StartLinuxApplication(argc, argv);
  
    return 0;
}
