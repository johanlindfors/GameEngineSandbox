#pragma once
#include "IInputManager.h"
#include <array>

namespace Engine {
    class InputManager : public IInputManager 
    {
    public:
		InputManager() {}
        void AddKeyboardEvent(int keyCode, bool isPressed);
        bool IsKeyDown(int keyCode);

    private:
		std::array<bool, 256> mKeyboard = {};
    };
}
