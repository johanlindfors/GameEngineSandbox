#pragma once
#include "MouseStates.h"

namespace Engine
{
    class IInputManager
    {
    public:
        virtual ~IInputManager() = default;
        virtual void addKeyboardEvent(int keyCode, bool isPressed) = 0;
        virtual bool isKeyDown(int keyCode) = 0;
        virtual void addMouseEvent(MouseButton button, MouseButtonState action, int x, int y) = 0;
        virtual MouseState getMouseState() = 0;
        virtual void update() = 0;
    };
}
