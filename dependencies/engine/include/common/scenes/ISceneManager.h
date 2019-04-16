#pragma once
#include "GameScene.h"
#include "StepTimer.h"

class ISceneManager {
public:
    virtual void Initialize() = 0;
	virtual void UpdateScreenSize(int width, int height) = 0;
    virtual void Update(Utilities::StepTimer const& timer) = 0;
    virtual void Draw(Utilities::StepTimer const& timer) = 0;
    virtual void AddScene(GameScene* scene) = 0;
    virtual void RemoveScene(GameScene* sceneId) = 0;
};