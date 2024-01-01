#pragma once

// stl
#include <memory>

// game
#include "MoveableObject.hpp"

namespace Engine
{
    class IStepTimer;
}

class Player : public MoveableObject
{
public:
    Player();
    ~Player() = default;

    void initialize(int x, int y);
    void move(int deltaX, int deltaY);
    void update(std::shared_ptr<Engine::IStepTimer> timer);
    int posX, posY;
};
