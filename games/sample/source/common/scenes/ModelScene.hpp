#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.hpp"
#include "resources/Model.hpp"
#include "utilities/MathHelper.hpp"

class IGameStateCallback;
namespace Engine
{
    class ModelRenderer;
    class IInputManager;
    class ISceneManager;
    class ResourceManager;
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
        std::shared_ptr<Engine::Model<Utilities::VertexPositionTexture>> mBody;
        std::shared_ptr<Engine::Model<Utilities::VertexPositionNormalTexture>> mCube;
        float angle;
        std::shared_ptr<Engine::IInputManager> mInputManager;
        std::shared_ptr<Engine::ISceneManager> mSceneManager;
        std::shared_ptr<Engine::ResourceManager> mResourceManager;
        bool mAnimate;
    };
}
