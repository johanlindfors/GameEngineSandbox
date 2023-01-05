#include "glwrapper.h"
#include "game-loop/GameLoop.h"
#include "utilities/IOC.hpp"
#include "utilities/Config.h"
#include "input/IInputManager.h"
#include "utilities/GLHelper.h"
#include <memory>

using namespace std;
using namespace Engine;
using namespace Utilities;

void inputHandler(GLFWwindow* window, shared_ptr<IInputManager> input);

void startOsxApplication(int argc, char **argv) {
    GLFWwindow* window;
    shared_ptr<IInputManager> input;

    auto game = std::make_unique<GameLoop>();
    printf("[StartOsxApplication] game created\n");
    auto config = IOCContainer::instance().resolve<Config>();
    printf("[StartOsxApplication] found config\n");

    int width, height;
    width = config->width;
    height = config->height;
    printf("[StartOsxApplication] GetDefaultSize returned\n");
    
    if(!glfwInit()) {
        printf("Initialization of GLFW failed!");
        exit(EXIT_FAILURE);
    }
  
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config->glMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config->glMinorVersion);
    if(config->glMajorVersion > 2) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
    printf("Creating window!\n");
    window = glfwCreateWindow(width, height, config->title.c_str(), NULL, NULL);
    if (!window)
    {
        printf("Creation of window failed!\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    printf("[StartOsxApplication] Creating Context\n");
    glfwMakeContextCurrent(window);
    glfwGetError(NULL);

    printf("GL_VERSION  : %s\n", glGetString(GL_VERSION) );
    printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER) );
    printf("GL_SHADING_LANGUAGE_VERSION : %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

    printf("[StartOsxApplication] Initializing game\n");
    game->initialize(config);
    printf("[StartOsxApplication] initialized\n");

    game->updateWindowSize(width, height);
    printf("[StartOsxApplication] Windows size updated\n");

    glfwSetWindowUserPointer(window, game.get());
    glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
    {
        auto game = static_cast<Engine::GameLoop*>(glfwGetWindowUserPointer(window));
        game->updateWindowSize(width, height);
        glViewport(0,0,width, height);
    });
    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT);

  	    if(game) {
            if(!input) {
		        input = game->getInput();
            }
            inputHandler(window, input);
	    }

        game->tick();
        glfwSwapBuffers(window);
    }
    
    glfwTerminate();
}

void inputHandler(GLFWwindow* window, shared_ptr<IInputManager> input) 
{
    // Check left
    bool pressed = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
    input->addKeyboardEvent(0x25, pressed);

    // Check right
    pressed = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
    input->addKeyboardEvent(0x27, pressed);
    
    // Check up
    pressed = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
    input->addKeyboardEvent(0x26, pressed);

    // Check down
    pressed = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
    input->addKeyboardEvent(0x28, pressed);

    // Space
    pressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
    input->addKeyboardEvent(32, pressed);
}
