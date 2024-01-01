#pragma once
#include <list>
#include "utilities/MathHelper.hpp"
#include <vector>
#include "physics/ICollidable.hpp"
#include "game/GameDefines.hpp"

namespace Engine
{
	class IStepTimer;
}

namespace Engine
{
	class IRenderer;
	struct Sprite;
}

class Ground
	: public Engine::ICollidable
{
public:
	Ground(Engine::Point<float> position, Engine::Vector2 velocity);
	void update(std::shared_ptr<Engine::IStepTimer> timer);
	void draw(std::shared_ptr<Engine::IRenderer> renderer);

	void pause() { mIsRunning = false; }
	void resume() { mIsRunning = true; }
	void initializeSprite();

private:
	std::vector<Engine::Point<float>> mGround;
	std::shared_ptr<Engine::Sprite> mGroundSprite;
	std::shared_ptr<Engine::Sprite> mGroundBackgroundSprite;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	std::shared_ptr<Engine::Sprite> mGroundDebugSprite;
#endif
	Engine::Vector2 mVelocity;
	Engine::Point<float> mPosition;
	int mGroundOffset;
	int mGroundBackgroundOffset;
	bool mIsRunning;
};
