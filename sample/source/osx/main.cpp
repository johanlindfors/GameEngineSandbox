#include "game/Bootstrap.hpp"

void StartOsxApplication(int argc, char** argv);

int
main(int argc, char **argv)
{
  Bootstrap();
  StartOsxApplication(argc, argv);
  return 0;             /* ANSI C requires main to return int. */
}