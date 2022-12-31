#include "glwrapper.h"
#include "game-loop/GameLoop.h"
#include "utilities/Config.h"
#include "utilities/IOC.hpp"
#include "input/IInputManager.h"
#include <memory>

using namespace std;
using namespace Engine;
using namespace Utilities;

void InputHandler(GLFWwindow* window, shared_ptr<IInputManager> input);

void StartLinuxApplication(int argc, char **argv) {
    GLFWwindow* window;
    shared_ptr<IInputManager> input;

    auto game = std::make_unique<GameLoop>();
    printf("[StartLinuxApplication] game created\n");
    auto config = IOCContainer::Instance().Resolve<Config>();
    printf("[StartLinuxApplication] found config\n");

    int width, height;
    width = config->Width;
    height = config->Height;
    printf("[StartLinuxApplication] get default size returned\n");
    
    glfwInit();
    glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config->GLMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config->GLMinorVersion);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, config->Title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);

    game->Initialize(config);
    printf("[StartLinuxApplication] initialized\n");

    game->UpdateWindowSize(width, height);
    printf("[StartLinuxApplication] Windows size updated\n");

    printf("GL_VERSION  : %s\n", glGetString(GL_VERSION));
    printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER));
    printf("GL_SHADING_LANGUAGE_VERSION : %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

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

        // Escape
        pressed = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
        input->AddKeyboardEvent(256, pressed);
}
