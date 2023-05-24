#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.h"

class IGameStateCallback;
namespace Engine
{
    class SpriteRenderer;
    class IInputManager;
    struct Sprite;
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
            SpriteScene() { id = typeid(SpriteScene).name(); }
            
            // Engine::GameScene
            void load() override;
            void unload() override;
            void updateScreenSize(int width, int height) override;
            void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
            void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

        private:
            std::shared_ptr<Engine::SpriteRenderer> mRenderer;
            std::shared_ptr<Engine::Sprite> mSprite;
            std::shared_ptr<Engine::IInputManager> mInputManager;
    };
}
