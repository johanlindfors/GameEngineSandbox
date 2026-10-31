#pragma once
#include <memory>
#include <vector>
#include "scenes/GameScene.hpp"

class IGameStateCallback;
namespace Engine
{
    class IInputManager;
    class IResourceManager;
    class ISceneManager;
    class IRenderer;
    class IAudioManager;
}

namespace Utilities
{
    class IStepTimer;
}

namespace Sample
{
    class AudioScene : public Engine::GameScene
    {
    public:
        AudioScene();
        
        // Engine::GameScene
        void load() override;
        void unload() override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
        void draw(std::shared_ptr<Engine::IRenderer> renderer) override;

    private:
        std::shared_ptr<Engine::IRenderer> mRenderer;
        std::shared_ptr<Engine::IInputManager> mInputManager;
        std::shared_ptr<Engine::ISceneManager> mSceneManager;
        std::shared_ptr<Engine::IResourceManager> mResourceManager;
        std::shared_ptr<Engine::IAudioManager> mAudioManager;
    };
}
