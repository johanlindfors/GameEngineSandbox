#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.hpp"
#include "game/Components.hpp"
#include "game/Systems.hpp"

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

namespace Sample 
{
    class SpriteScene : public Engine::GameScene 
    {
        public:
            SpriteScene() 
                : mSpriteSystem(std::make_unique<SpriteSystem>())
	        { id = typeid(SpriteScene).name(); }
            
            // Engine::GameScene
            void load() override;
            void unload() override;
            void updateScreenSize(int width, int height) override;
            void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
            void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

        private:
            std::shared_ptr<Engine::SpriteRenderer> mRenderer;
            std::shared_ptr<Engine::TiledSprite> mSprite;
            std::shared_ptr<Engine::IInputManager> mInputManager;

            entt::registry mRegistry;
            std::unique_ptr<SpriteSystem> mSpriteSystem;
    };
}
