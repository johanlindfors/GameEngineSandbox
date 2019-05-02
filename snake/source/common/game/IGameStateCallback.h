#pragma once
#include "GameState.h"

class IGameStateCallback {
public:
    virtual void GoToState(GameState gameState) = 0;
	virtual GameState GetCurrentState() = 0;
};