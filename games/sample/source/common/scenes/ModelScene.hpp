#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.hpp"

class IGameStateCallback;
namespace Engine
{
    class ModelRenderer;
    class Model;
    class IInputManager;
    class ISceneManager;
    class IResourceManager;
}

namespace Utilities
{
    class IStepTimer;
}

namespace Sample
{
    class ModelScene : public Engine::GameScene
    {
    public:
        ModelScene();

        // Engine::GameScene
        void load() override;
        void unload() override;
        void updateScreenSize(int width, int height) override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
        void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

    private:
        std::shared_ptr<Engine::ModelRenderer> mRenderer;
        std::vector<std::shared_ptr<Engine::Model>> mModels;
        float angle;
        std::shared_ptr<Engine::IInputManager> mInputManager;
        std::shared_ptr<Engine::ISceneManager> mSceneManager;
        std::shared_ptr<Engine::IResourceManager> mResourceManager;
        bool mAnimate;
    };
}
