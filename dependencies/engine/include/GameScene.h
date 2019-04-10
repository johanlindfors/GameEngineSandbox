#pragma once
#include "StepTimer.h"

class GameScene {
public:
    GameScene();

	void UpdateScreenSize(int width, int height);
	void Update(Utilities::StepTimer const& timer);
	void Draw(Utilities::StepTimer const& timer);
};