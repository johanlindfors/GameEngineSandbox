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
        ~Player();
        
        void initialize(int x, int y);
	    void update(std::shared_ptr<Utilities::IStepTimer> timer);
	    void draw(std::shared_ptr<Engine::IRenderer> renderer);
};