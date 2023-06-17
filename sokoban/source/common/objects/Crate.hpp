#pragma once

#include <memory>
#include "MoveableObject.hpp"

namespace Engine
{
    class IRenderer;
}

namespace Utilities
{
    class IStepTimer;
}

class Crate : public MoveableObject
{
    public:
        Crate(int x, int y);
        ~Crate() = default;
        int index;
};
