#include <emscripten.h>
#include "utilities/glwrapper.hpp"
#include "game-loop/GameLoop.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"
#include "input/IInputManager.hpp"
#include "utilities/ScreenToGameCoordinatesConverter.hpp"
#include <memory>
#include "utilities/Logger.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

GLFWwindow *window;
std::unique_ptr<GameLoop> game;

void mainLoop() {
    glfwPollEvents();
    game->tick();
    glfwSwapBuffers(window);
    debuglog.flush();
}

void startApplication(int argc, char **argv)
{
    game = std::make_unique<GameLoop>();
    debuglog << "[StartLinuxApplication] game created" << endl;
    auto config = IOCContainer::instance().resolve<Config>();
    debuglog << "[StartLinuxApplication] found config" << endl;

    int width, height;
    width = config->width;
    height = config->height;
    debuglog << "[StartLinuxApplication] get default size returned" << endl;

    glfwInit();
    // glfwWindowHint(GLFW_CLIENT_API, GLFW_OPENGL_ES_API);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, config->glMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, config->glMinorVersion);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width, height, config->title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(window);
    glfwSwapInterval(0);

    debuglog << "GL_VERSION  : " << glGetString(GL_VERSION) << endl;
    debuglog << "GL_RENDERER : " << glGetString(GL_RENDERER) << endl;
    debuglog << "GL_SHADING_LANGUAGE_VERSION : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    game->initialize(config);
    debuglog << "[StartLinuxApplication] initialized" << endl;
    game->ScreenToGameCoordinatesConverter.setGameSize({width,height});
    game->updateWindowSize(width, height);
    debuglog << "[StartLinuxApplication] Windows size updated" << endl;

    debuglog << "GL_VERSION  : " << glGetString(GL_VERSION) << endl;
    debuglog << "GL_RENDERER : " << glGetString(GL_RENDERER) << endl;
    debuglog << "GL_SHADING_LANGUAGE_VERSION : " << glGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    glfwSetWindowUserPointer(window, game.get());
    glfwSetWindowSizeCallback(window, [](GLFWwindow *window, int width, int height) {
        auto game = static_cast<Engine::GameLoop*>(glfwGetWindowUserPointer(window));
        game->updateWindowSize(width, height);
        GlViewport(0,0,width, height); });

    glfwSetMouseButtonCallback(window, [](GLFWwindow *window, int button, int action, int mods) {
        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            double xpos, ypos;
            glfwGetCursorPos(window, &xpos, &ypos);
            auto input = IOCContainer::instance().resolve<IInputManager>();
            auto game = static_cast<Engine::GameLoop*>(glfwGetWindowUserPointer(window));
            auto gameAspects = game->ScreenToGameCoordinatesConverter.getAspects();
            auto scaledX = xpos * gameAspects.width;
            auto scaledY = ypos * gameAspects.height;
            if(action == GLFW_PRESS) {
                debuglog << "Mouse (" << xpos << ", " << ypos << ") down" << std::endl;
                input->addMouseEvent(MouseButton::Left, ButtonState::Pressed, scaledX, scaledY);
            } else if(action == GLFW_RELEASE) {
                debuglog << "Mouse (" << xpos << ", " << ypos << ") up" << std::endl;
                input->addMouseEvent(MouseButton::Left, ButtonState::Released, scaledX, scaledY);
            }
        }
    });

    glfwSetKeyCallback(window, [](GLFWwindow *window, int key, int scancode, int action, int mods) {
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

    emscripten_set_main_loop(&mainLoop, 0, 1);
    
    game.reset();
    glfwTerminate();
}
