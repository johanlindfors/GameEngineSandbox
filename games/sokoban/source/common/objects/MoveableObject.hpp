#pragma once

// stl
#include <memory>
#include <functional>

namespace Engine
{
    class Sprite;
    class IRenderer;
}

namespace Utilities
{
    class ITweenEngine;
}

class MoveableObject
{
public:
    MoveableObject();
    ~MoveableObject() = default;
    void draw(std::shared_ptr<Engine::IRenderer> renderer);
    virtual void move(int deltaX, int deltaY, std::function<void()> onCompleteCallback);

    bool isMoving;
    void setFrame(int frame);

protected:
    std::shared_ptr<Engine::Sprite> mSprite;
};
