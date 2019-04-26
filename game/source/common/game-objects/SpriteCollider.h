#pragma once
#include <memory>

namespace Engine
{
    struct Sprite;
}

class SpriteCollider {
public:
    bool CollidesOnPosition(std::shared_ptr<Engine::Sprite> sprite1, std::shared_ptr<Engine::Sprite> sprite2) const;
};
