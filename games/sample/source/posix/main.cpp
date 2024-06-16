#include <iostream>
#include "game/Bootstrap.hpp"

void startApplication(int argc, char **argv);

int main(int argc, char **argv)
{
    setbuf(stdout, NULL);
    bootstrap();
    startApplication(argc, argv);
  
    return 0;
}
