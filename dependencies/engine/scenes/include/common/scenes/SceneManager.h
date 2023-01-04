#pragma once
#include "ISceneManager.h"
#include <vector>

namespace Engine {

    class SceneManager : public ISceneManager {
    public:
        SceneManager();
        ~SceneManager();

    	// Engine::ISceneManager
        void Initialize() override;
        void UpdateScreenSize(int width, int height) override;
        void Update(std::shared_ptr<Utilities::IStepTimer> timer) override;
        void Draw(std::shared_ptr<IRenderer> renderer) override;
        void AddScene(std::shared_ptr<GameScene> scene) override;
        void RemoveScene(const std::type_info& sceneType) override;

    private:
        bool mInitialized;
        std::vector<std::shared_ptr<GameScene>> mScenes;
        std::vector<std::shared_ptr<GameScene>> mScenesToUpdate;
		int mScreenWidth;
		int mScreenHeight;
    };
}
