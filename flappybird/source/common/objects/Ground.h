#pragma once
#include <list>
#include "utilities/MathHelper.h"
#include <vector>
#include "physics/ICollidable.h"
#include "game/GameDefines.h"

namespace Utilities
{
	class IStepTimer;
}

namespace Engine
{
	class IRenderer;
	struct Sprite;
}

class Ground
	: public Engine::ICollidable {
public:
	Ground(Utilities::Point<float> position, Utilities::Vector2 velocity);
	void update(std::shared_ptr<Utilities::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);

    void pause() { mIsRunning = false; }
    void resume() { mIsRunning = true; }
	void initializeSprite();
	
private:
	std::vector<Utilities::Point<float>> mGround;
	std::shared_ptr<Engine::Sprite> mGroundSprite;
	std::shared_ptr<Engine::Sprite> mGroundBackgroundSprite;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	std::shared_ptr<Engine::Sprite> mGroundDebugSprite;	
#endif
	Utilities::Vector2 mVelocity;
	Utilities::Point<float> mPosition;
	int mGroundOffset;
	int mGroundBackgroundOffset;
    bool mIsRunning;
};
