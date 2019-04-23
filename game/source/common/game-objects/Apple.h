#pragma once
#include "Entity.h"
#include "MathHelper.h"
#include "sprites/ISpriteRenderer.h"
#include <memory>

class Apple : public Entity {
public:
	Apple(Utilities::Vector2 position);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);
	void Update(int screenWidth, int screenHeight);
	void Reset();

private:
	Utilities::Vector2 mScreenPosition;
};
