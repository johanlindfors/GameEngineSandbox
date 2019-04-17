#pragma once
#include "IInputManager.h"
#include <concurrent_vector.h>

class InputManager : public IInputManager 
{
public:
    void AddKeyboardEvent(int keyCode, bool isPressed);
    bool IsKeyDown(int keyCode);
    void ProcessEvents();

private:
    struct KeyboardEvent {
        KeyboardEvent(int keyCode, bool isPressed)
            : mKeyCode(keyCode)
            , mIsPressed(isPressed) { }
        int mKeyCode;
        bool mIsPressed;
    };

    concurrency::concurrent_vector<KeyboardEvent> mKeyboardEvents;
};
