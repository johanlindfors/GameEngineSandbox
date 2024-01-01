#pragma once
#include "utilities/MathHelper.hpp"

namespace Engine
{
    enum ButtonState
    {
        None,
        Pressed,
        Released,
        Repeat
    };

    enum MouseButton
    {
        Left,
        Right,
        Middle
    };

    struct MouseState
    {
        MouseButton button;
        ButtonState state;
        Engine::Point<int> position;

        MouseState()
            : position{0, 0}, button(MouseButton::Left), state(ButtonState::None)
        {
        }
    };
}
