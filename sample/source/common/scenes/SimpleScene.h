#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.h"

namespace Utilities
{
    class IStepTimer;
}

namespace Sample 
{
    class SimpleScene : public Engine::GameScene 
    {
        public:
            explicit SimpleScene() = default;

            // Engine::GameScene
            void draw(std::shared_ptr<Engine::IRenderer> renderer) override;
    };
}
