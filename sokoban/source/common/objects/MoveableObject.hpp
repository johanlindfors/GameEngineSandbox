#pragma once
#include <memory>

namespace Engine
{
    class Sprite;
}

class MoveableObject 
{
    public:
        MoveableObject();
        ~MoveableObject();

    protected:
        std::shared_ptr<Engine::Sprite> mSprite; 
};