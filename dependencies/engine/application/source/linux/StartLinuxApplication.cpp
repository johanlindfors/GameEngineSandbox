#include "glwrapper.h"
#include "game-loop/GameLoop.h"
#include "application/Config.h"
#include "IOC.hpp"
#include <memory>

using namespace std;
using namespace Engine;
using namespace Utilities;

void StartLinuxApplication(int argc, char **argv) {
    GLFWwindow* window;

    auto game = std::make_unique<GameLoop>();
    printf("[StartLinuxApplication] game created\n");
    auto config = IOCContainer::Instance().Resolve<Config>();
    printf("[StartLinuxApplication] found config\n");
    game->Initialize(config->FPS);
    printf("[StartLinuxApplication] initialized\n");

    int width, height;
    game->GetDefaultSize(width, height);
    printf("[StartLinuxApplication] get default size returned\n");
    
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    window = glfwCreateWindow(width, height, __FILE__, NULL, NULL);
    glfwMakeContextCurrent(window);

    game->UpdateWindowSize(width, height);
    printf("[StartLinuxApplication] Windows size updated\n");

    printf("GL_VERSION  : %s\n", glGetString(GL_VERSION) );
    printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER) );

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);
        game->Tick();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
}
