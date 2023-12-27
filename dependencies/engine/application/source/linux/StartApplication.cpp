#include "utilities/glwrapper.hpp"
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
        GLFWwindow *window;

        auto game = std::make_unique<GameLoop>();
        printf("[StartLinuxApplication] game created\n");
        auto config = IOCContainer::instance().resolve<Config>();
        printf("[StartLinuxApplication] found config\n");

        int width, height;
        width = config->width;
        height = config->height;
        printf("[StartLinuxApplication] get default size returned\n");

        glfwInit();
        // glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config->glMajorVersion);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config->glMinorVersion);
        glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
        window = glfwCreateWindow(width, height, config->title.c_str(), NULL, NULL);
        glfwMakeContextCurrent(window);
        glfwSwapInterval(0);

        printf("GL_VERSION  : %s\n", glGetString(GL_VERSION));
        printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER));
        printf("GL_SHADING_LANGUAGE_VERSION : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

        game->initialize(config);
        printf("[StartLinuxApplication] initialized\n");

        game->updateWindowSize(width, height);
        printf("[StartLinuxApplication] Windows size updated\n");

        printf("GL_VERSION  : %s\n", glGetString(GL_VERSION));
        printf("GL_RENDERER : %s\n", glGetString(GL_RENDERER));
        printf("GL_SHADING_LANGUAGE_VERSION : %s\n", glGetString(GL_SHADING_LANGUAGE_VERSION));

        glfwSetWindowUserPointer(window, game.get());
        glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height)
                                  {
                auto game = static_cast<Engine::GameLoop*>(glfwGetWindowUserPointer(window));
                game->updateWindowSize(width, height);
                GlViewport(0,0,width, height); });

        glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods)
                                   {
                if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
                    double xpos, ypos;
                    glfwGetCursorPos(window, &xpos, &ypos);
                    auto input = IOCContainer::instance().resolve<IInputManager>();
                    input->addMouseEvent(MouseButton::Left, ButtonState::Pressed, xpos, ypos);
                } });

        glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods)
                           {
                auto input = IOCContainer::instance().resolve<IInputManager>();
                ButtonState state(ButtonState::None);
                switch (action) {
                    case GLFW_PRESS:
                        state = ButtonState::Pressed;
                        break;
                    case GLFW_REPEAT:
                        state = ButtonState::Repeat;
                        break;
                    case GLFW_RELEASE:
                        state = ButtonState::Released;
                        break;
                    default:
                        break;
                }
                switch(key) {
                    case GLFW_KEY_LEFT:
                        input->addKeyboardEvent(0x25, state);
                        break;
                    case GLFW_KEY_RIGHT:
                        input->addKeyboardEvent(0x27, state);
                        break;
                    case GLFW_KEY_UP:
                        input->addKeyboardEvent(0x26, state);
                        break;
                    case GLFW_KEY_DOWN:
                        input->addKeyboardEvent(0x28, state);
                        break;
                    case GLFW_KEY_SPACE:
                        input->addKeyboardEvent(0x20, state);
                        break;
                    case GLFW_KEY_ESCAPE:
                        glfwSetWindowShouldClose(window, 1);
                        break;
                    default:
                        break;
                } });

        while (!glfwWindowShouldClose(window))
        {
            glfwPollEvents();
            glClear(GL_COLOR_BUFFER_BIT);

            game->tick();
            glfwSwapBuffers(window);
        }
        game.reset();
        glfwTerminate();
    }

private:
    shared_ptr<IInputManager> mInput;
};

void startApplication(int argc, char **argv)
{
    Application application;
    application.start();
}
