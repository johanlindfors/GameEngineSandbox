#include "glwrapper.hpp"
#include "game-loop/GameLoop.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"
#include "input/IInputManager.hpp"
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
            printf("[StartOsxApplication] game created\n");
            auto config = IOCContainer::instance().resolve<Config>();
            printf("[StartOsxApplication] found config\n");

            int width, height;
            width = config->width;
            height = config->height;
            printf("[StartOsxApplication] get default size returned\n");
            
            glfwInit();
            glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config->glMajorVersion);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config->glMinorVersion);
            glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
            window = glfwCreateWindow(width, height, config->title.c_str(), NULL, NULL);
            glfwMakeContextCurrent(window);
            glfwSwapInterval(0);

            printf("GL_VERSION  : %s\n", glGetString(GL_VERSION));
            printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER));
            printf("GL_SHADING_LANGUAGE_VERSION : %s\n",glGetString(GL_SHADING_LANGUAGE_VERSION));

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

            glfwSetKeyCallback(window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
            {
                auto input = IOCContainer::instance().resolve<IInputManager>();
                bool pressed = action != GLFW_RELEASE;
                switch(key) {
                    case GLFW_KEY_LEFT:
                        input->addKeyboardEvent(0x25, pressed);
                        break;
                    case GLFW_KEY_RIGHT:
                        input->addKeyboardEvent(0x27, pressed);
                        break;
                    case GLFW_KEY_UP:
                        input->addKeyboardEvent(0x26, pressed);
                        break;
                    case GLFW_KEY_DOWN:
                        input->addKeyboardEvent(0x28, pressed);
                        break;
                    case GLFW_KEY_SPACE:
                        input->addKeyboardEvent(0x20, pressed);
                        break;
                    case GLFW_KEY_ESCAPE:
                        input->addKeyboardEvent(0xFF, pressed);
                        break;
                    default:
                        break;
                }
            });

            glfwSetMouseButtonCallback(window, [](GLFWwindow* window, int button, int action, int mods)
            {
                if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                    double xpos, ypos;
                    glfwGetCursorPos(window, &xpos, &ypos);
                    auto input = IOCContainer::instance().resolve<IInputManager>();
                    input->addMouseEvent(MouseButton::Left, MouseButtonState::Pressed, xpos, ypos);
                }
            });

            while (!glfwWindowShouldClose(window)) {
                glfwPollEvents();
                glClear(GL_COLOR_BUFFER_BIT);
                game->tick();
                glfwSwapBuffers(window);
            }
            game.reset();
            glfwTerminate();
        }
};

void startApplication(int argc, char **argv) {
    Application application;
    application.start();
}
