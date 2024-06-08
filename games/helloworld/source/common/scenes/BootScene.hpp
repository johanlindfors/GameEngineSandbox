#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.hpp"
#include <functional>

namespace Engine
{
    class IRenderer;
}

namespace Utilities
{
    class IStepTimer;
}

namespace HelloWorld::Scenes
{
    class BootScene : public Engine::GameScene
    {
    public:
        BootScene() { id = typeid(BootScene).name();}

        // Engine::GameScene
        void load() override;
        void unload() override;
        void updateScreenSize(int width, int height) override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
        void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

    private:
        bool mResourcesLoaded = false;
    };
}
