#pragma once
#include "IInputManager.hpp"
#include <array>
#include <queue>

namespace Engine
{
    class InputManager : public IInputManager
    {
    public:
        InputManager() = default;
        void addKeyboardEvent(int keyCode, bool isPressed) override;
        bool isKeyDown(int keyCode) override;
        void addMouseEvent(MouseButton button, MouseButtonState state, int x, int y) override;
        MouseState getMouseState() override;
        void update() override;

    private:
        std::array<bool, 256> mKeyboard = {};
        std::queue<MouseState> mMouseStates = {};
    };
}
