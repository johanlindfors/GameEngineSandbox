#pragma once
#include "GameScene.h"
#include "StepTimer.h"
#include <vector>
#include <memory>

class SceneManager {
public:
    SceneManager();
    void Initialize();
	void UpdateScreenSize(int width, int height);
    void Update(Utilities::StepTimer const& timer);
    void Draw(Utilities::StepTimer const& timer);
    void AddScene(std::shared_ptr<GameScene> scene);
    void RemoveScene(std::shared_ptr<GameScene> scene);

private:
	bool mInitialized;
    std::vector<std::shared_ptr<GameScene>> mScenes;
	std::vector<std::shared_ptr<GameScene>> mScenesToUpdate;
};