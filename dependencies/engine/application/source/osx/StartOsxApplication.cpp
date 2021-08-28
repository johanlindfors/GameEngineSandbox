#include "game-loop/GameLoop.h"
#include "glwrapper.h"
#include <GL/glut.h>
#include <memory>
#include "input/IInputManager.h"
#include "application/Config.h"
#include "IOC.hpp"

using namespace Engine;
using namespace Utilities;

namespace {
  std::unique_ptr<GameLoop> g_gameLoop;
};

void
reshape(int w, int h)
{
  g_gameLoop->UpdateWindowSize(w,h);
}

void
display(void)
{
  g_gameLoop->Tick();
  glFlush();  /* Single buffered, so needs a flush. */
}

void StartOsxApplication(int argc, char **argv)
{
  g_gameLoop = std::make_unique<GameLoop>();
  auto config = IOCContainer::Instance().Resolve<Config>();
  g_gameLoop->Initialize(config->FPS);
  int width, height;
  g_gameLoop->GetDefaultSize(width, height);
  g_gameLoop->UpdateWindowSize(width, height);

  glutInit(&argc, argv);
  glutCreateWindow("a snake");
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutMainLoop();
  
  g_gameLoop.reset();
}