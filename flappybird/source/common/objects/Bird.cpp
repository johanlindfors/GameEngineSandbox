#include "Bird.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "MathHelper.h"
#include "renderer/Sprite.h"
#include "IStepTimer.h"

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
#ifdef _DEBUG
	, mDebugSprite(make_shared<Sprite>())
#endif
{
    mSprite->Width = 33;
	mSprite->Height = 24;
}

void Bird::Reset() {
	mSprite->Position = Vector2(132, 300);
}

void Bird::Update(shared_ptr<IStepTimer> timer)
{
    Entity::Update(timer);
	if(mAnimationCounter++ >= mFramesPerAnimation) {
		auto offset = mSprite->Offset;
		offset++;
		offset %= 3;
		mSprite->Offset = offset;
		mAnimationCounter = 0;
	}

	AABB = Rectangle(X,
					 Y,
					 mSprite->Width,
					 mSprite->Height);
	Bounds = Circle(X + mSprite->Width/2,
					Y + mSprite->Height/2,
					16);
#ifdef _DEBUG
	mDebugSprite->Position = Vector2(AABB.X, AABB.Y);
	mDebugSprite->Offset = 22;
	mDebugSprite->Width = AABB.Width;
	mDebugSprite->Height = AABB.Height;
#endif
}

void Bird::Flap()
{
	if(IsAlive) {
		Velocity.m[1] = 400;
	}
}

void Bird::Draw(shared_ptr<ISpriteRenderer> renderer) {
#ifdef _DEBUG
	renderer->DrawSprite(mDebugSprite, Vector2(X, Y));
#endif
	renderer->DrawSprite(mSprite, Vector2(X, Y));
}
