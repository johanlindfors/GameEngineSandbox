#pragma once
#include "IInputManager.h"
#include <array>

namespace Engine {
    class InputManager : public IInputManager 
    {
    public:
		InputManager() {}
        void AddKeyboardEvent(int keyCode, bool isPressed) override;
        bool IsKeyDown(int keyCode) override;

    private:
		std::array<bool, 256> mKeyboard = {};
    };
}
