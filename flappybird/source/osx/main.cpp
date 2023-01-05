#include <iostream>
#include "game/Bootstrap.hpp"

void startOsxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);

    bootstrap();

    auto config = IOCContainer::instance().resolve<Config>();
    config->glMajorVersion = 2;
    config->glMinorVersion = 1;
    startOsxApplication(argc, argv);
  
    return 0;
}
