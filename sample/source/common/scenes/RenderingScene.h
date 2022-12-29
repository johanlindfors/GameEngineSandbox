#pragma once
#include <memory>
#include "scenes/GameScene.h"

class IGameStateCallback;

namespace Engine
{
    class ISpriteRenderer;
    class SimpleRenderer;
}

namespace Utilities
{
    class IStepTimer;
}

namespace Sample 
{
    class RenderingScene : public Engine::GameScene 
    {
        public:
            RenderingScene(IGameStateCallback* gameCallback)
                : mGameCallback(gameCallback)
                { }
            
            // Engine::GameScene
            void Load() override;
            void Unload() override;
            void UpdateScreenSize(int width, int height) override;
            void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
            void Draw(std::shared_ptr<Engine::IRenderer> renderer) override;

        private:
            std::shared_ptr<Engine::SimpleRenderer> mRenderer;
            IGameStateCallback* mGameCallback;
    };}
