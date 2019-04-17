#pragma once
#include "GameScene.h"
#include "StepTimer.h"
#include <memory>

class ISceneManager {
public:
    virtual void Initialize() = 0;
	virtual void UpdateScreenSize(int width, int height) = 0;
    virtual void Update(Utilities::StepTimer const& timer) = 0;
    virtual void Draw(Utilities::StepTimer const& timer) = 0;
    virtual void AddScene(std::shared_ptr<GameScene> scene) = 0;
    virtual void RemoveScene(const char* sceneId) = 0;
};