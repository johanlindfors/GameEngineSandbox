#include "game/Bootstrap.hpp"

void startOsxApplication(int argc, char **argv);

int main(int argc, char **argv)
{
  bootstrap();
  startOsxApplication(argc, argv);
  return 0; /* ANSI C requires main to return int. */
}