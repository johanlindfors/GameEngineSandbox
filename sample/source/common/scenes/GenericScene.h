#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.h"
#include "resources/Model.h"
#include "resources/GenericShader.h"

class IGameStateCallback;

namespace Utilities
{
    class IStepTimer;
}

namespace Sample 
{
    class GenericScene : public Engine::GameScene 
    {
        public:
            GenericScene(IGameStateCallback* gameCallback)
                : mGameCallback(gameCallback)
                { }
            
            // Engine::GameScene
            void Load() override;
            void Unload() override;
            void UpdateScreenSize(int width, int height) override;
            void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
            void Draw(std::shared_ptr<Engine::IRenderer> renderer) override;

        private:
            std::vector<Engine::Model> mModels;
            std::unique_ptr<Engine::GenericShader> mShader;
            IGameStateCallback* mGameCallback;
            int mWidth, mHeight;
    };
}
