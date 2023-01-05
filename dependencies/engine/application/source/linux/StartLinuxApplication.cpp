#include "glwrapper.h"
#include "game-loop/GameLoop.h"
#include "utilities/Config.h"
#include "utilities/IOC.hpp"
#include "input/IInputManager.h"
#include <memory>

using namespace std;
using namespace Engine;
using namespace Utilities;

class Application
{
    public:
        void start() 
        {
            GLFWwindow* window;
            
            auto game = std::make_unique<GameLoop>();
            printf("[StartLinuxApplication] game created\n");
            auto config = IOCContainer::instance().resolve<Config>();
            printf("[StartLinuxApplication] found config\n");

            int width, height;
            width = config->width;
            height = config->height;
            printf("[StartLinuxApplication] get default size returned\n");
            
            glfwInit();
            glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config->glMajorVersion);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config->glMinorVersion);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            window = glfwCreateWindow(width, height, config->title.c_str(), NULL, NULL);
            glfwMakeContextCurrent(window);
            glfwSwapInterval(0);

            printf("GL_VERSION  : %s\n", glGetString(GL_VERSION));
            printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER));
            printf("GL_SHADING_LANGUAGE_VERSION : %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

            game->initialize(config);
            printf("[StartLinuxApplication] initialized\n");

            game->updateWindowSize(width, height);
            printf("[StartLinuxApplication] Windows size updated\n");

            printf("GL_VERSION  : %s\n", glGetString(GL_VERSION));
            printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER));
            printf("GL_SHADING_LANGUAGE_VERSION : %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

            glfwSetWindowUserPointer(window, game.get());
            glfwSetWindowSizeCallback(window, [](GLFWwindow* window, int width, int height)
            {
                auto game = static_cast<Engine::GameLoop*>(glfwGetWindowUserPointer(window));
                game->updateWindowSize(width, height);
                glViewport(0,0,width, height);
            });

            glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods) {
                if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                    double xpos, ypos;
                    glfwGetCursorPos(window, &xpos, &ypos);
                    auto input = IOCContainer::instance().resolve<IInputManager>();
                    input->addMouseEvent(MouseButton::Left, MouseButtonState::Pressed, xpos, 505 - ypos);
                    printf("Mouse down: %lf, %lf", xpos, ypos);
                }
            });

            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
                glClear(GL_COLOR_BUFFER_BIT);

                if(game) {
                    if(!mInput) {
                        mInput = game->getInput();
                    }
                    inputHandler(window);
                }

                game->tick();
                glfwSwapBuffers(window);
            }
            game.reset();
            glfwTerminate();
        }

    private:
        void inputHandler(GLFWwindow* window) 
        {
            // Check left
            bool pressed = glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS;
            mInput->addKeyboardEvent(0x25, pressed);

            // Check right
            pressed = glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS;
            mInput->addKeyboardEvent(0x27, pressed);
            
            // Check up
            pressed = glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS;
            mInput->addKeyboardEvent(0x26, pressed);

            // Check down
            pressed = glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS;
            mInput->addKeyboardEvent(0x28, pressed);

            // Space
            pressed = glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS;
            mInput->addKeyboardEvent(32, pressed);

            // Escape
            pressed = glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS;
            mInput->addKeyboardEvent(256, pressed);
        }

        shared_ptr<IInputManager> mInput;
};

void startLinuxApplication(int argc, char **argv) {
    Application application;
    application.start();
}
