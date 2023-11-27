#include "Application.h"

#include <game-activity/native_app_glue/android_native_app_glue.h>
#include <memory>
#include <vector>
#include <cassert>

#include "utilities/glwrapper.hpp"
#include "utilities/Logger.hpp"
#include "utilities/AndroidWrapper.hpp"

Application::~Application() {
    if (display_ != EGL_NO_DISPLAY) {
        eglMakeCurrent(display_, EGL_NO_SURFACE, EGL_NO_SURFACE, EGL_NO_CONTEXT);
        if (context_ != EGL_NO_CONTEXT) {
            eglDestroyContext(display_, context_);
            context_ = EGL_NO_CONTEXT;
        }
        if (surface_ != EGL_NO_SURFACE) {
            eglDestroySurface(display_, surface_);
            surface_ = EGL_NO_SURFACE;
        }
        eglTerminate(display_);
        display_ = EGL_NO_DISPLAY;
    }
}

void Application::render() {
    // Check to see if the surface has changed size. This is _necessary_ to do every frame when
    // using immersive mode as you'll get no other notification that your renderable area has
    // changed.
    updateRenderArea();

    // clear the color buffer
    glClear(GL_COLOR_BUFFER_BIT);

    mGameLoop->tick();

    // Present the rendered image. This is an implicit glFlush.
    auto swapResult = eglSwapBuffers(display_, surface_);
    assert(swapResult == EGL_TRUE);
}

void Application::initApplication() {
    mGameLoop = std::make_unique<Engine::GameLoop>();
    debuglog << "[Application::initApplication] game was created" << std::endl;
    auto gameConfig = Utilities::IOCContainer::instance().resolve<Utilities::Config>();
    debuglog << "[Application::initApplication] was launched with the game: " << gameConfig->title << std::endl;
    auto androidWrapper = std::make_shared<AndroidWrapper>(app_);
    Utilities::IOCContainer::instance().register_type<AndroidWrapper>(androidWrapper);

    // Choose your render attributes
    constexpr EGLint attribs[] = {
            EGL_RENDERABLE_TYPE, EGL_OPENGL_ES3_BIT,
            EGL_SURFACE_TYPE, EGL_WINDOW_BIT,
            EGL_BLUE_SIZE, 8,
            EGL_GREEN_SIZE, 8,
            EGL_RED_SIZE, 8,
            EGL_DEPTH_SIZE, 24,
            EGL_NONE
    };

    // The default display is probably what you want on Android
    auto display = eglGetDisplay(EGL_DEFAULT_DISPLAY);
    eglInitialize(display, nullptr, nullptr);

    // figure out how many configs there are
    EGLint numConfigs;
    eglChooseConfig(display, attribs, nullptr, 0, &numConfigs);

    // get the list of configurations
    std::unique_ptr<EGLConfig[]> supportedConfigs(new EGLConfig[numConfigs]);
    eglChooseConfig(display, attribs, supportedConfigs.get(), numConfigs, &numConfigs);

    // Find a config we like.
    // Could likely just grab the first if we don't care about anything else in the config.
    // Otherwise hook in your own heuristic
    auto config = *std::find_if(
            supportedConfigs.get(),
            supportedConfigs.get() + numConfigs,
            [&display](const EGLConfig &config) {
                EGLint red, green, blue, depth;
                if (eglGetConfigAttrib(display, config, EGL_RED_SIZE, &red)
                    && eglGetConfigAttrib(display, config, EGL_GREEN_SIZE, &green)
                    && eglGetConfigAttrib(display, config, EGL_BLUE_SIZE, &blue)
                    && eglGetConfigAttrib(display, config, EGL_DEPTH_SIZE, &depth)) {

                    debuglog << "Found config with " << red << ", " << green << ", " << blue << ", "
                             << depth << std::endl;
                    return red == 8 && green == 8 && blue == 8 && depth == 24;
                }
                return false;
            });

    debuglog << "Found " << numConfigs << " configs" << std::endl;
    debuglog << "Chose " << config << std::endl;

    // create the proper window surface
    EGLint format;
    eglGetConfigAttrib(display, config, EGL_NATIVE_VISUAL_ID, &format);
    EGLSurface surface = eglCreateWindowSurface(display, config, app_->window, nullptr);

    // Create a GLES 3 context
    EGLint contextAttribs[] = {EGL_CONTEXT_CLIENT_VERSION, 3, EGL_NONE};
    EGLContext context = eglCreateContext(display, config, nullptr, contextAttribs);

    // get some window metrics
    auto madeCurrent = eglMakeCurrent(display, surface, surface, context);
    assert(madeCurrent);

    display_ = display;
    surface_ = surface;
    context_ = context;

    // make width and height invalid so it gets updated the first frame in @a updateRenderArea()
    width_ = -1;
    height_ = -1;

    PRINT_GL_STRING(GL_VENDOR);
    PRINT_GL_STRING(GL_RENDERER);
    PRINT_GL_STRING(GL_VERSION);
    PRINT_GL_STRING_AS_LIST(GL_EXTENSIONS);

    // enable alpha globally for now, you probably don't want to do this in a game
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    mGameLoop->initialize(gameConfig);
}

void Application::updateRenderArea() {
    EGLint width;
    eglQuerySurface(display_, surface_, EGL_WIDTH, &width);

    EGLint height;
    eglQuerySurface(display_, surface_, EGL_HEIGHT, &height);

    if (width != width_ || height != height_) {
        width_ = width;
        height_ = height;
        glViewport(0, 0, width, height);
    }
}

void Application::handleInput() {
    if(mInputManager == nullptr) {
        mInputManager = Utilities::IOCContainer::instance().resolve<Engine::IInputManager>();
        assert(mInputManager);
    }

    // handle all queued inputs
    auto *inputBuffer = android_app_swap_input_buffers(app_);
    if (!inputBuffer) {
        // no inputs yet.
        return;
    }

    // handle motion events (motionEventsCounts can be 0).
    for (auto i = 0; i < inputBuffer->motionEventsCount; i++) {
        auto &motionEvent = inputBuffer->motionEvents[i];
        auto action = motionEvent.action;

        // Find the pointer index, mask and bitshift to turn it into a readable value.
        auto pointerIndex = (action & AMOTION_EVENT_ACTION_POINTER_INDEX_MASK)
                >> AMOTION_EVENT_ACTION_POINTER_INDEX_SHIFT;
        debuglog << "Pointer(s): ";

        // get the x and y position of this event if it is not ACTION_MOVE.
        auto &pointer = motionEvent.pointers[pointerIndex];
        auto x = GameActivityPointerAxes_getX(&pointer);
        auto y = GameActivityPointerAxes_getY(&pointer);

        // determine the action type and process the event accordingly.
        switch (action & AMOTION_EVENT_ACTION_MASK) {
            case AMOTION_EVENT_ACTION_DOWN:
            case AMOTION_EVENT_ACTION_POINTER_DOWN:
                debuglog << "(" << pointer.id << ", " << x << ", " << y << ") "
                         << "Pointer Down";
                mInputManager->addMouseEvent(Engine::MouseButton::Left, Engine::ButtonState::Pressed, x, y);
                break;

            case AMOTION_EVENT_ACTION_CANCEL:
                // treat the CANCEL as an UP event: doing nothing in the app, except
                // removing the pointer from the cache if pointers are locally saved.
                // code pass through on purpose.
            case AMOTION_EVENT_ACTION_UP:
            case AMOTION_EVENT_ACTION_POINTER_UP:
                debuglog << "(" << pointer.id << ", " << x << ", " << y << ") "
                         << "Pointer Up";
                mInputManager->addMouseEvent(Engine::MouseButton::Left, Engine::ButtonState::Released, x, y);
                break;

            case AMOTION_EVENT_ACTION_MOVE:
                // There is no pointer index for ACTION_MOVE, only a snapshot of
                // all active pointers; app needs to cache previous active pointers
                // to figure out which ones are actually moved.
                for (auto index = 0; index < motionEvent.pointerCount; index++) {
                    pointer = motionEvent.pointers[index];
                    x = GameActivityPointerAxes_getX(&pointer);
                    y = GameActivityPointerAxes_getY(&pointer);
                    debuglog << "(" << pointer.id << ", " << x << ", " << y << ")";

                    if (index != (motionEvent.pointerCount - 1)) debuglog << ",";
                    debuglog << " ";
                    mInputManager->addMouseEvent(Engine::MouseButton::Left,Engine::ButtonState::Repeat, x, y);
                }
                debuglog << "Pointer Move";
                break;
            default:
                debuglog << "Unknown MotionEvent Action: " << action;
        }
        debuglog << std::endl;
    }
    // clear the motion input count in this buffer for main thread to re-use.
    android_app_clear_motion_events(inputBuffer);

    // handle input key events.
    for (auto i = 0; i < inputBuffer->keyEventsCount; i++) {
        auto &keyEvent = inputBuffer->keyEvents[i];
        debuglog << "Key: " << keyEvent.keyCode <<" ";
        switch (keyEvent.action) {
            case AKEY_EVENT_ACTION_DOWN:
                mInputManager->addKeyboardEvent(keyEvent.keyCode, Engine::ButtonState::Pressed);
                debuglog << "Key Down";
                break;
            case AKEY_EVENT_ACTION_UP:
                mInputManager->addKeyboardEvent(keyEvent.keyCode, Engine::ButtonState::Released);
                debuglog << "Key Up";
                break;
            case AKEY_EVENT_ACTION_MULTIPLE:
                // Deprecated since Android API level 29.
                debuglog << "Multiple Key Actions";
                break;
            default:
                debuglog << "Unknown KeyEvent Action: " << keyEvent.action;
        }
        debuglog << std::endl;
    }
    // clear the key input count too.
    android_app_clear_key_events(inputBuffer);
}
