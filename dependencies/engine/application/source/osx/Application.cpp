#include "Application.hpp"
// Engine
#include "game-loop/GameLoop.hpp"
#include "input/IInputManager.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"
#include "utilities/ScreenToGameCoordinatesConverter.hpp"
#include "utilities/Logger.hpp"
// stl
#include <memory>

using namespace std;
using namespace Engine;

Application::Application() {
    mGame = std::make_unique<GameLoop>();
    mConfig = IOCContainer::instance().resolve<Config>();
    debuglog << "[StartOsxApplication] game created" << endl;
    
    setupWindow();
    setupCallbacks();
}

Application::~Application() {
    debuglog << "[StartOsxApplication] game destroyed" << endl;
    mGame.reset();
    glfwTerminate();
}

void Application::run() {
    while (!glfwWindowShouldClose(mWindow))
    {
        glfwPollEvents();
        mGame->tick();
        glfwSwapBuffers(mWindow);
    }
}

void Application::setupWindow()
{
    int width = mConfig->width;
    int height = mConfig->height;

    glfwInitHint(GLFW_COCOA_CHDIR_RESOURCES, GLFW_FALSE);
    glfwInit();
    glfwWindowHint(GLFW_COCOA_RETINA_FRAMEBUFFER, GLFW_FALSE);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, mConfig->glMajorVersion);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, mConfig->glMinorVersion);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
    mWindow = glfwCreateWindow(width, height, mConfig->title.c_str(), NULL, NULL);
    glfwMakeContextCurrent(mWindow);
    glfwSwapInterval(0);

    debuglog << "GL_VERSION  : " << GlGetString(GL_VERSION) << endl;
    debuglog << "GL_RENDERER : " << GlGetString(GL_RENDERER) << endl;
    debuglog << "GL_SHADING_LANGUAGE_VERSION : " << GlGetString(GL_SHADING_LANGUAGE_VERSION) << endl;

    mGame->initialize(mConfig);
    debuglog << "[StartOsxApplication] initialized" << endl;
    mGame->ScreenToGameCoordinatesConverter.setGameSize({width, height});
    mGame->updateWindowSize(width, height);
    
    glfwSetWindowUserPointer(mWindow, mGame.get());
}

void Application::setupCallbacks() {
    glfwSetWindowSizeCallback(mWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(mWindow, glfwKeyCallback);
    glfwSetMouseButtonCallback(mWindow, glfwMouseButtonCallback);
}

void Application::glfwWindowSizeCallback(GLFWwindow *window, int width, int height)
{
    auto game = static_cast<Engine::GameLoop*>(glfwGetWindowUserPointer(window));
    game->updateWindowSize(width, height);
    GlViewport(0,0,width, height); 
};

void Application::glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods)
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
    }
};

void Application::glfwMouseButtonCallback(GLFWwindow *window, int button, int action, int mods)
{
    if (button == GLFW_MOUSE_BUTTON_LEFT) {
        double xpos, ypos;
        glfwGetCursorPos(window, &xpos, &ypos);
        auto input = IOCContainer::instance().resolve<IInputManager>();
        auto game = static_cast<Engine::GameLoop*>(glfwGetWindowUserPointer(window));
        auto gameAspects = game->ScreenToGameCoordinatesConverter.getAspects();
        auto scaledX = xpos * gameAspects.width;
        auto scaledY = ypos * gameAspects.height;
        if(action == GLFW_PRESS) {
            input->addMouseEvent(MouseButton::Left, ButtonState::Pressed, scaledX, scaledY);
        } else {
            input->addMouseEvent(MouseButton::Left, ButtonState::Released, scaledX, scaledY);
        }
    } 
};
