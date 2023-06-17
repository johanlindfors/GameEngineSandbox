#pragma once
#include <memory>
#include <functional>

namespace Engine
{
    class Sprite;
    class IRenderer;
}

namespace Utilities
{
    class IStepTimer;
    class ITweenEngine;
}

class MoveableObject 
{
    public:
        MoveableObject();
        ~MoveableObject();
        void update(std::shared_ptr<Utilities::IStepTimer> timer);
        void draw(std::shared_ptr<Engine::IRenderer> renderer);
        virtual void move(int deltaX, int deltaY);
        virtual void move(int deltaX, int deltaY, std::function<void()> onCompleteCallback);

        bool isMoving;
        void setFrame(int frame);

    protected:
        std::shared_ptr<Engine::Sprite> mSprite;
        int mFrame;
        std::shared_ptr<Utilities::ITweenEngine> mTweenEngine;
};