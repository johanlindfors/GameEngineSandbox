#include "Snake.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "MathHelper.h"
#include "renderer/Sprite.h"
#include "game/IGameStateCallback.h"

using std::shared_ptr;
using Utilities::Vector2;
using Engine::ISpriteRenderer;
using Engine::IInputManager;

Bird::Bird(Vector2 position)
    : Entity(position)
{
    mSprite->Velocity = Vector2(0.0f, 1.0f);
}

void Bird::Reset() {
	mSprite->Position = Vector2(10, 10);
}

void Bird::Update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback)
{
    Entity::Update(screenWidth, screenHeight);
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

}
