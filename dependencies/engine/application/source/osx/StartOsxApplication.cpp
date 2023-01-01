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

void InputHandler(GLFWwindow* window, shared_ptr<IInputManager> input);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

void StartOsxApplication(int argc, char **argv) {
    GLFWwindow* window;
    shared_ptr<IInputManager> input;

    auto game = std::make_unique<GameLoop>();
    printf("[StartOsxApplication] game created\n");
    auto config = IOCContainer::Instance().Resolve<Config>();
    printf("[StartOsxApplication] found config\n");

    int width, height;
    width = config->Width;
    height = config->Height;
    printf("[StartOsxApplication] GetDefaultSize returned\n");
    
    if(!glfwInit()) {
        printf("Initialization of GLFW failed!");
        exit(EXIT_FAILURE);
    }
  
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    //glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config->GLMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config->GLMinorVersion);
    if(config->GLMajorVersion > 2) {
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    }
    printf("Creating window!\n");
    window = glfwCreateWindow(width, height, config->Title.c_str(), NULL, NULL);
    if (!window)
    {
        printf("Creation of window failed!\n");
        glfwTerminate();
        exit(EXIT_FAILURE);
    }
    
    glfwSetMouseButtonCallback(window, mouse_button_callback);

    printf("[StartOsxApplication] Creating Context\n");
    glfwMakeContextCurrent(window);

    glfwGetError(NULL);
    printf("[StartOsxApplication] Initializing game\n");
    game->Initialize(config);
    printf("[StartOsxApplication] initialized\n");

    game->UpdateWindowSize(width, height);
    printf("[StartOsxApplication] Windows size updated\n");

    printf("GL_VERSION  : %s\n", glGetString(GL_VERSION) );
    printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER) );
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
}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        auto input = IOCContainer::Instance().Resolve<IInputManager>();
        input->AddMouseEvent(MouseButton::Left, MouseButtonState::Pressed, xpos, 505 - ypos);
        printf("Mouse down: %lf, %lf", xpos, ypos);
    }
}
