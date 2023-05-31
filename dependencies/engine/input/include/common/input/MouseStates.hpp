#pragma once
#include "utilities/MathHelper.hpp"

namespace Engine
{
    enum MouseButtonState {
        None,
        Pressed,
        Released,
        Repeat
    };

    enum MouseButton {
        Left,
        Right,
        Middle
    };
    
    struct MouseState {
        MouseButton button;
        MouseButtonState state;
        Utilities::Point<int> position;

        MouseState() 
            : position{0,0}
            , button(MouseButton::Left)
            , state(MouseButtonState::None)
            { }
    };
}