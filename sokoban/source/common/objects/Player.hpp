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

class Player : public MoveableObject
{
    public:
        Player();
        ~Player() = default;
        
        void initialize(int x, int y);
        // void move(int deltaX, int deltaY) override;

        int posX, posY;
};