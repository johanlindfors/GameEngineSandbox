#pragma once
#include "MouseStates.hpp"

namespace Engine
{
    class IInputManager
    {
    public:
        virtual ~IInputManager() = default;
        virtual void addKeyboardEvent(int keyCode, ButtonState state) = 0;
        virtual bool isKeyDown(int keyCode) = 0;
        virtual void addMouseEvent(MouseButton button, ButtonState action, int x, int y) = 0;
        virtual MouseState getMouseState() = 0;
        virtual void update() = 0;
    };
}
