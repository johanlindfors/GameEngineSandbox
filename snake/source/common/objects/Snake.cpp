#include "Snake.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "utilities/MathHelper.h"
#include "renderer/Sprite.h"
#include "game/IGameStateCallback.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Snake::Snake(Point<float> position)
    : Entity(position)
{
    mTail = INITIAL_TAIL;	
    mSprite->Velocity = Vector2(0.0f, 1.0f);
}

bool Snake::CheckCollision(int x, int y) {
    for (auto const& body : mTrail) {
        if (body.X == x && body.Y == y) {
            return true;
        }
    }
    return false;
}

void Snake::IncreaseLength() {
	mTail += 1;
}

void Snake::Reset() {
	mTail = INITIAL_TAIL;
	mSprite->Position = Point<float>(10, 10);
}

void Snake::Update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback)
{
    Entity::Update(screenWidth, screenHeight);

	auto const newX = static_cast<int>(mSprite->Position.X + mSprite->Velocity.m[0] + SCREEN_SIZE) % SCREEN_SIZE;
	auto const newY = static_cast<int>(mSprite->Position.Y + mSprite->Velocity.m[1] + SCREEN_SIZE) % SCREEN_SIZE;

	if (CheckCollision(newX, newY)) {
		gameCallback->GoToState(GameState::GameOver);
	}
	else {
		mSprite->Position.X = newX;
		mSprite->Position.Y = newY;

		mTrail.push_back({ mSprite->Position });
		while (mTrail.size() > mTail) {
			mTrail.pop_front();
		}
	}
}

void Snake::HandleInput(shared_ptr<IInputManager> input)
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

void Snake::Draw(shared_ptr<ISpriteRenderer> renderer) {
	for (auto const& body : mTrail)
	{
        renderer->DrawSprite(mSprite, Point<float>(body.X * mScreenWidth / SCREEN_SIZE, body.Y * mScreenHeight / SCREEN_SIZE));
    }
}
