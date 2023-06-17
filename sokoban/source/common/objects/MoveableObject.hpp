#pragma once
#include <memory>
#include <functional>

namespace Engine
{
    class Sprite;
    class IRenderer;
}

class MoveableObject 
{
    public:
        MoveableObject();
        ~MoveableObject();
        void update();
        void draw(std::shared_ptr<Engine::IRenderer> renderer);
        void move(int deltaX, int deltaY);
        void move(int deltaX, int deltaY, std::function<void()> onCompleteCallback);

        bool isMoving;
        void setFrame(int frame);

    protected:
        std::shared_ptr<Engine::Sprite> mSprite;
        int mFrame;
};