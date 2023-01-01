#include <iostream>
#include "game/Bootstrap.hpp"

void StartOsxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    Bootstrap();

    auto config = IOCContainer::Instance().Resolve<Config>();
    config->GLMajorVersion = 2;
    config->GLMinorVersion = 1;
    StartOsxApplication(argc, argv);
  
    return 0;
}
