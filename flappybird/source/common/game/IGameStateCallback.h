#pragma once
#include "GameState.h"

class IGameStateCallback {
public:
	virtual ~IGameStateCallback() = default;
	virtual void goToState(GameState gameState) = 0;
	virtual GameState getCurrentState() = 0;
};