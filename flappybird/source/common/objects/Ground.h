#pragma once
#include "Entity.h"
#include <list>
#include "MathHelper.h"
#include <vector>

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class ISpriteRenderer;
	class Sprite;
}

class Ground {
public:
	Ground(Utilities::Vector2 position, Utilities::Vector2 velocity);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);

private:
	std::vector<std::shared_ptr<Engine::Sprite>> mGround;
	std::shared_ptr<Engine::Sprite> mGroundBackground;
	Utilities::Vector2 mVelocity;
	Utilities::Vector2 mPosition;
	int mGroundOffset;
	int mGroundBackgroundOffset;
};
