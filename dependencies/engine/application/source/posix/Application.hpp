#pragma once
// GLFW
#include <GLFW/glfw3.h>
// stl
#include <memory>

namespace Engine
{
    class GameLoop;
    struct Config;

    class Application
    {
    public:
        Application();
        ~Application();
        void run();

    private: 
        void setupWindow();
        void setupCallbacks();

        static void glfwWindowSizeCallback(GLFWwindow *window, int width, int height);
        static void glfwKeyCallback(GLFWwindow *window, int key, int scancode, int action, int mods);
        static void glfwMouseButtonCallback(GLFWwindow *window, int button, int action, int mods);

        GLFWwindow *mWindow;
        std::unique_ptr<Engine::GameLoop> mGame;
        std::shared_ptr<Engine::Config> mConfig;
    };        
}
