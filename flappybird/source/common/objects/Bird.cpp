#include "Bird.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "MathHelper.h"
#include "renderer/Sprite.h"
#include "IStepTimer.h"

using std::shared_ptr;
using Utilities::Vector2;
using Utilities::IStepTimer;
using Engine::ISpriteRenderer;
using Engine::IInputManager;

Bird::Bird(Vector2 position)
    : Entity(position)
	, IPhysicsBody(position)
	, mAnimationCounter(0)
	, mFramesPerAnimation(4)
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
}

void Bird::Flap()
{
	if(IsAlive) {
		Velocity.m[1] = 400;
	}
}

void Bird::Draw(shared_ptr<ISpriteRenderer> renderer) {
	renderer->DrawSprite(mSprite, Vector2(X, Y));
}
