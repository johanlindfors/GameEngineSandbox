#pragma once
#include "ISceneManager.h"
#include <vector>
#include <memory>

class SceneManager : public ISceneManager {
public:
    SceneManager();
    void Initialize();
	void UpdateScreenSize(int width, int height);
    void Update(Utilities::StepTimer const& timer);
    void Draw(Utilities::StepTimer const& timer);
    void AddScene(GameScene* scene);
    void RemoveScene(GameScene* sceneId);

private:
	bool mInitialized;
    std::vector<GameScene*> mScenes;
	std::vector<GameScene*> mScenesToUpdate;
};