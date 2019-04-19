#pragma once
#include "ISceneManager.h"
#include <vector>

namespace Engine {

    class SceneManager : public ISceneManager {
    public:
        SceneManager();
        void Initialize();
        void UpdateScreenSize(int width, int height);
        void Update(Utilities::StepTimer const& timer);
        void Draw(Utilities::StepTimer const& timer);
        void AddScene(std::shared_ptr<GameScene> scene);
        void RemoveScene(const char* sceneId);

    private:
        bool mInitialized;
        std::vector<std::shared_ptr<GameScene>> mScenes;
        std::vector<std::shared_ptr<GameScene>> mScenesToUpdate;
		int mScreenWidth;
		int mScreenHeight;
    };
}
