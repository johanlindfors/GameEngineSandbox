#include <iostream>
#include "game/Bootstrap.hpp"

void startOsxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    bootstrap();
    startOsxApplication(argc, argv);
  
    return 0;
}
