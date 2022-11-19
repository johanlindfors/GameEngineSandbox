#include "glwrapper.h"
#include "game-loop/GameLoop.h"
#include "application/Config.h"
#include "IOC.hpp"
#include "input/IInputManager.h"
#include "GLHelper.h"
#include <memory>

using namespace std;
using namespace Engine;
using namespace Utilities;

void InputHandler(GLFWwindow* window, shared_ptr<IInputManager> input);

void StartOsxApplication(int argc, char **argv) {
    GLFWwindow* window;
    shared_ptr<IInputManager> input;

    auto game = std::make_unique<GameLoop>();
    printf("[StartOsxApplication] game created\n");
    auto config = IOCContainer::Instance().Resolve<Config>();
    printf("[StartOsxApplication] found config\n");

    int width, height;
    game->GetDefaultSize(width, height);
    printf("[StartOsxApplication] GetDefaultSize returned\n");
    
    glfwInit();
    printf("[StartOsxApplication] GLFW Initialized\n");
    Engine::CheckOpenGLError();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    printf("[StartOsxApplication] GLFW Window Hint\n");
    Engine::CheckOpenGLError();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    printf("[StartOsxApplication] GLFW Version 2\n");
    Engine::CheckOpenGLError();
    printf("[StartOsxApplication] GLFW .0\n");
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
    Engine::CheckOpenGLError();
    printf("[StartOsxApplication] Creating Window\n");
    window = glfwCreateWindow(width, height, __FILE__, NULL, NULL);
    printf("[StartOsxApplication] Creating Context\n");
    glfwMakeContextCurrent(window);

    printf("[StartOsxApplication] Initializing game\n");
    game->Initialize(config->FPS);
    printf("[StartOsxApplication] initialized\n");

    game->UpdateWindowSize(width, height);
    printf("[StartOsxApplication] Windows size updated\n");

    printf("GL_VERSION  : %s\n", glGetString(GL_VERSION) );
    printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER) );

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

  	    if(game) {
            if(!input) {
		        input = game->GetInput();
            }
            InputHandler(window, input);
	    }

        game->Tick();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
}

void InputHandler(GLFWwindow* window, shared_ptr<IInputManager> input) 
{
        // Check left
        bool pressed = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
        input->AddKeyboardEvent(0x25, pressed);

        // Check right
        pressed = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
        input->AddKeyboardEvent(0x27, pressed);
        
        // Check up
        pressed = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
        input->AddKeyboardEvent(0x26, pressed);

        // Check down
        pressed = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
        input->AddKeyboardEvent(0x28, pressed);

        // Space
        pressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
        input->AddKeyboardEvent(32, pressed);

}
