#pragma once
#include "utilities/MathHelper.h"

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
        MouseButton Button;
        MouseButtonState State;
        Utilities::Point<int> Position;

        MouseState() 
            : Position(0,0)
            { }
    };
}
