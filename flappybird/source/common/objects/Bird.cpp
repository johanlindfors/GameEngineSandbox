#include "Bird.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "utilities/ITweenEngine.h"
#include "utilities/MathHelper.h"
#include "renderer/Sprite.h"
#include "utilities/IStepTimer.h"
#include "utilities/IOC.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Bird::Bird(Vector2 position)
    : Entity(position)
	, IPhysicsBody(position)
	, mAnimationCounter(0)
	, mFramesPerAnimation(4)
	, Bounds(Circle(position.m[0]+16, position.m[1]+12, 16))
	, AABB(Rectangle(0, 0, 0, 0))
	, IsKilled(false)
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	, mDebugSprite(make_shared<Sprite>())
#endif
{
    mSprite->Width = 33;
	mSprite->Height = 24;
}

void Bird::Reset() {
	mSprite->Position = Vector2(80, 300);
	X = 80;
	Y = 300;
	mSprite->Rotation = 0;
	mAnimationCounter = 0;
	IsKilled = false;
	IsAlive = true;
	AllowGravity = true;
	Flap();
}

void Bird::Update(shared_ptr<IStepTimer> timer)
{
	if(IsAlive) {
		Entity::Update(timer);
		if(mAnimationCounter++ >= mFramesPerAnimation) {
			auto offset = mSprite->Offset;
			offset++;
			offset %= 3;
			mSprite->Offset = offset;
			mAnimationCounter = 0;
		}

		if (mSprite->Rotation > -90 && IsAlive)
		{
			mSprite->Rotation -= 2.5f;
		}

		AABB = Rectangle(X,
						Y,
						mSprite->Width,
						mSprite->Height);
		Bounds = Circle(X + mSprite->Width/2,
						Y + mSprite->Height/2,
						16);
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		mDebugSprite->Position = Vector2(AABB.X, AABB.Y);
		mDebugSprite->Offset = 22;
		mDebugSprite->Width = AABB.Width;
		mDebugSprite->Height = AABB.Height;
#endif
	}
}

void Bird::Flap()
{
	if(IsAlive && !IsKilled) {
		Velocity.m[1] = 400;

		auto tweenEngine = IOCContainer::Instance().Resolve<ITweenEngine>();
		tweenEngine->Add(mSprite->Rotation, [&](int value)
		{
 			mSprite->Rotation = value;
		}, 40, 100, false);
	}
}

void Bird::CollideWithPipe()
{
	IsKilled = true;
}

void Bird::Draw(shared_ptr<ISpriteRenderer> renderer) {
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	renderer->DrawSprite(mDebugSprite, Vector2(X, Y));
#endif
	renderer->DrawSprite(mSprite, Vector2(X, Y));
}
