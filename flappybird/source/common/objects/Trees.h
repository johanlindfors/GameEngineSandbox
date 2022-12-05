#pragma once
#include "Entity.h"
#include <list>
#include "utilities/MathHelper.h"

namespace Utilities
{
	class IStepTimer;	
}

namespace Engine
{
	class ISpriteRenderer;
	class Sprite;
}

class Trees {
public:
	Trees(Utilities::Vector2 position, Utilities::Vector2 velocity);
	void Update(std::shared_ptr<Utilities::IStepTimer> timer);
	void Draw(std::shared_ptr<Engine::ISpriteRenderer> renderer);

private:
	std::shared_ptr<Engine::Sprite> mTrees;
	std::shared_ptr<Engine::Sprite> mTreesBackground;
	Utilities::Vector2 mVelocity;
	Utilities::Vector2 mPosition;
	int mCloudsOffset;
	int mCloudsBackgroundOffset;
};