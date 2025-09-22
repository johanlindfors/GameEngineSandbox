#pragma once
// thirdparty
#include <memory>
#include <vector>
// engine
#include "game/Components.hpp"
#include "game/Systems.hpp"
#include "scenes/GameScene.hpp"

class IGameStateCallback;
namespace Engine
{
    class SpriteRenderer;
    class IInputManager;
    struct TiledSprite;
    class OrthographicCamera;
}

namespace Utilities
{
    class IStepTimer;
}

namespace Sample
{
    class SpriteScene : public Engine::GameScene
    {
    public:
        SpriteScene()
            : mSpriteSystem(std::make_unique<SpriteSystem>())
            , mPositionSystem(std::make_unique<PositionSystem>())
            , mMouseDownX(0), mMouseDownY(0)
        {
            id = typeid(SpriteScene).name();
        }

        // Engine::GameScene
        void load() override;
        void unload() override;
        void updateScreenSize(int width, int height) override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
        void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

    private:
        void placeTile(int x, int y, int tile, int zOrder);
        std::shared_ptr<Engine::SpriteRenderer> mRenderer;
        std::shared_ptr<Engine::TiledSprite> mSprite;
        std::shared_ptr<Engine::IInputManager> mInputManager;
        std::shared_ptr<Engine::OrthographicCamera> mCamera;

        entt::registry mRegistry;
        std::unique_ptr<SpriteSystem> mSpriteSystem;
        std::unique_ptr<PositionSystem> mPositionSystem;

        int mMouseDownX;
        int mMouseDownY;
    };
}
