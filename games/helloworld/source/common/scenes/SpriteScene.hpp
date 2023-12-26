#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.hpp"

class IGameStateCallback;
namespace Engine
{
    class SpriteRenderer;
    class IInputManager;
    struct TiledSprite;
}

namespace Utilities
{
    class IStepTimer;
}

namespace HelloWorld::Scenes
{
    class SpriteScene : public Engine::GameScene
    {
    public:
        SpriteScene() { id = typeid(SpriteScene).name(); }

        // Engine::GameScene
        void load() override;
        void unload() override;
        void updateScreenSize(int width, int height) override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override { };
        void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

    private:
        std::shared_ptr<Engine::TiledSprite> mSprite;
    };
}
