#pragma once
#include "IInputManager.h"
#include <concurrent_vector.h>
#include <array>

namespace Engine {
    class InputManager : public IInputManager 
    {
    public:
		InputManager() {}
        void AddKeyboardEvent(int keyCode, bool isPressed);
        bool IsKeyDown(int keyCode);

    private:
        struct KeyboardEvent {
            KeyboardEvent(int keyCode, bool isPressed)
                : mKeyCode(keyCode)
                , mIsPressed(isPressed) { }
            int mKeyCode;
            bool mIsPressed;
        };

		std::array<bool, 256> mKeyboard = {};
    };
}
