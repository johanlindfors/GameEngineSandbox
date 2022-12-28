#include "Bird.h"
#include "game/GameDefines.h"
#include "renderers/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "utilities/ITweenEngine.h"
#include "utilities/MathHelper.h"
#include "renderers/Sprite.h"
#include "utilities/IStepTimer.h"
#include "utilities/IOC.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Bird::Bird(Point<float> position)
    : IPhysicsBody(position)
	, Bounds(Circle(position.X+16, position.X+12, 12))
	, AABB(Utilities::Rectangle(0, 0, 0, 0))
	, IsKilled(false)
	, mAnimationCounter(0)
	, mFramesPerAnimation(4)
	, mSprite(make_shared<Sprite>())
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	, mDebugSprite(make_shared<Sprite>())
#endif
{
    mSprite->Width = 33;
	mSprite->Height = 24;
}

void Bird::Reset() {
	Position = Point<float>(85.0f, SCREEN_HEIGHT/2.0f-12);
	Velocity = Vector2(0.0f, 0.0f);
	mSprite->Rotation = 0;
	mAnimationCounter = 0;
	IsKilled = false;
	IsAlive = true;
	AllowGravity = false;
}

void Bird::Update(shared_ptr<IStepTimer> timer)
{
	if(IsAlive) {
		if(Position.Y >=465){
			Position.Y = 465;
		}
		if(mAnimationCounter++ >= mFramesPerAnimation) {
			auto offset = mSprite->Offset;
			offset++;
			offset %= 3;
			mSprite->Offset = offset;
			mAnimationCounter = 0;
		}

		if (AllowGravity && mSprite->Rotation > -90 && IsAlive)
		{
			mSprite->Rotation -= (160.0f * timer->GetElapsedMilliSeconds() / 1000.0f);
		}

		AABB = Utilities::Rectangle(Position.X,
						Position.Y,
						mSprite->Width,
						mSprite->Height);
		Bounds = Circle(Position.X + mSprite->Width/2,
						Position.Y + mSprite->Height/2,
						12);
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		mDebugSprite->Position = Point<float>(AABB.Position.X, AABB.Position.Y);
		mDebugSprite->Offset = 22;
		mDebugSprite->Width = AABB.Width;
		mDebugSprite->Height = AABB.Height;
#endif
	}
}

void Bird::Flap()
{
	if(IsAlive && !IsKilled) {
		AllowGravity = true;
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
	renderer->DrawSprite(mDebugSprite, Position);
#endif
	renderer->DrawSprite(mSprite, Point<float>(Position.X, Position.Y));
}
