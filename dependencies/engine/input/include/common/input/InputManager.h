#pragma once
#include "IInputManager.h"
#include <array>
#include <queue>

namespace Engine
{
    class InputManager : public IInputManager
    {
    public:
        InputManager() {}
        void addKeyboardEvent(int keyCode, bool isPressed) override;
        bool isKeyDown(int keyCode) override;
        bool isKeyDown(int keyCode) override;
        MouseState getMouseState() override;
        void update();

    private:
        std::array<bool, 256> mKeyboard = {};
        std::queue<MouseState> mMouseStates = {};
    };
}
