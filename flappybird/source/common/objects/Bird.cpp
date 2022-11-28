#include "Bird.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "MathHelper.h"
#include "renderer/Sprite.h"
#include "game/IGameStateCallback.h"
#include "IStepTimer.h"

using std::shared_ptr;
using Utilities::Vector2;
using Utilities::IStepTimer;
using Engine::ISpriteRenderer;
using Engine::IInputManager;

Bird::Bird(Vector2 position)
    : Entity(position)
	// , mAnimationCounter(0)
	// , mFramesPerAnimation(1)
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
	// if(mAnimationCounter++ >= mFramesPerAnimation) {
		auto offset = mSprite->Offset;
		offset++;
		offset %= 3;
		mSprite->Offset = offset;
		mAnimationCounter = 0;
	// }
}

void Bird::HandleInput(shared_ptr<IInputManager> input)
{
	if (mSprite->Velocity.m[0] == 0) {
		if (input->IsKeyDown(37)) {
			mSprite->Velocity = Utilities::Vector2(-1.0f, 0.0f);
		}
		if (input->IsKeyDown(39)) {
			mSprite->Velocity = Utilities::Vector2(1.0f, 0.0f);
		}
	}
	if (mSprite->Velocity.m[1] == 0) {
		if (input->IsKeyDown(40)) {
			mSprite->Velocity = Utilities::Vector2(0.0f, 1.0f);
		}
		if (input->IsKeyDown(38)) {
			mSprite->Velocity = Utilities::Vector2(0.0f, -1.0f);
		}
	}
}

void Bird::Draw(shared_ptr<ISpriteRenderer> renderer) {
	renderer->DrawSprite(mSprite);
}
