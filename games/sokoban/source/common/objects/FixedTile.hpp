#pragma once
#include <memory>
#include <cstdio>

namespace Engine
{
    class TiledSprite;
    class IRenderer;
}

class FixedTile
{
    public:
        FixedTile(int x, int y, int frame);
        ~FixedTile() = default;

        void draw(std::shared_ptr<Engine::IRenderer> renderer);

    private:
        std::shared_ptr<Engine::TiledSprite> mSprite;
};
