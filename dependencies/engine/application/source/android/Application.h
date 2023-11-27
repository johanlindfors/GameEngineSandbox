#pragma once

#include "utilities/glwrapper.hpp"
#include "game-loop/GameLoop.hpp"
#include "utilities/Config.hpp"
#include "utilities/IOC.hpp"
#include "input/IInputManager.hpp"
#include <memory>

struct android_app;

class Application {
public:
    /*!
     * @param pApp the android_app this Renderer belongs to, needed to configure GL
     */
    inline Application(android_app *pApp) :
            app_(pApp),
            display_(EGL_NO_DISPLAY),
            surface_(EGL_NO_SURFACE),
            context_(EGL_NO_CONTEXT),
            width_(0),
            height_(0) {
        initApplication();
    }

    virtual ~Application();

    /*!
     * Handles input from the android_app.
     *
     * Note: this will clear the input queue
     */
    void handleInput();

    /*!
     * Renders all the models in the renderer
     */
    void render();

private:
    /*!
     * Performs necessary OpenGL initialization. Customize this if you want to change your EGL
     * context or application-wide settings.
     */
    void initApplication();

    /*!
     * @brief we have to check every frame to see if the framebuffer has changed in size. If it has,
     * update the viewport accordingly
     */
    void updateRenderArea();

    android_app *app_;
    EGLDisplay display_;
    EGLSurface surface_;
    EGLContext context_;
    EGLint width_;
    EGLint height_;

    std::shared_ptr<Engine::GameLoop> mGameLoop;
    std::shared_ptr<Engine::IInputManager> mInputManager;
};
