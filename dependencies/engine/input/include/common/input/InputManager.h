#pragma once
#include "IInputManager.h"
#include <array>

namespace Engine {
    class InputManager : public IInputManager 
    {
    public:
		InputManager() {}
        void addKeyboardEvent(int keyCode, bool isPressed) override;
        bool isKeyDown(int keyCode) override;

    private:
		std::array<bool, 256> mKeyboard = {};
    };
}
