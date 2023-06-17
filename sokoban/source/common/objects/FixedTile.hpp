#pragma once
#include <memory>

namespace Engine
{
    class Sprite;
    class IRenderer;
}

class FixedTile
{
    public:
        FixedTile(int x, int y, int frame);
        ~FixedTile() = default;

        void draw(std::shared_ptr<Engine::IRenderer> renderer);

    private:
        std::shared_ptr<Engine::Sprite> mSprite;
};