#include <iostream>
#include "game/Bootstrap.hpp"

void StartOsxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    Bootstrap();

    StartOsxApplication(argc, argv);
  
    return 0;
}
