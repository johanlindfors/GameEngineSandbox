#pragma once
#include "Entity.h"
#include "sprites/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include <memory>
#include <list>

class Snake : public Entity {
public:
	Snake(Utilities::Vector2 position);
	bool CheckCollision(int x, int y);
	void Update(int screenWidth, int screenHeight);
	void HandleInput(std::shared_ptr<Engine::IInputManager> input);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);

private:
	int mTail;
	std::list<Utilities::Vector2> mTrail;
};