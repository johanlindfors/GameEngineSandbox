#pragma once
#include <memory>
#include "MoveableObject.hpp"

namespace Utilities
{
    class IStepTimer;
}

class Player : public MoveableObject
{
    public:
        Player();
        ~Player() { printf("[Player::destructor]\n"); };
        
        void initialize(int x, int y);
        void move(int deltaX, int deltaY);
        void update(std::shared_ptr<Utilities::IStepTimer> timer);
        int posX, posY;
};
