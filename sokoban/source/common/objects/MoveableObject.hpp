#pragma once
#include <memory>

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

        bool isMoving;

    protected:
        std::shared_ptr<Engine::Sprite> mSprite;
        int mFrame;
};