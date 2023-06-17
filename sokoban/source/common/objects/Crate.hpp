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
        ~Crate();
        int index;
        void initialize();
	    void update(std::shared_ptr<Utilities::IStepTimer> timer);
	    void draw(std::shared_ptr<Engine::IRenderer> renderer);
};
