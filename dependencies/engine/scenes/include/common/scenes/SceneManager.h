#pragma once
#include "ISceneManager.h"
#include <vector>

namespace Engine {

    class SceneManager : public ISceneManager {
    public:
        SceneManager();
        ~SceneManager();

    	// Engine::ISceneManager
        void initialize() override;
        void updateScreenSize(int width, int height) override;
        void update(std::shared_ptr<Utilities::IStepTimer> timer) override;
        void draw(std::shared_ptr<IRenderer> renderer) override;
        void addScene(std::shared_ptr<GameScene> scene) override;
        void removeScene(const std::type_info& sceneType) override;

    private:
        bool mInitialized;
        std::vector<std::shared_ptr<GameScene>> mScenes;
        std::vector<std::shared_ptr<GameScene>> mScenesToUpdate;
		int mScreenWidth;
		int mScreenHeight;
    };
}
