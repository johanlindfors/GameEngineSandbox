#include "Snake.h"
#include "game/GameDefines.h"
#include "renderers/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "utilities/MathHelper.h"
#include "renderers/Sprite.h"
#include "game/IGameStateCallback.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Snake::Snake(Point<int> position)
    : Entity(position)
{
    mTail = INITIAL_TAIL;	
    mSprite->Velocity = Vector2{0.0f, 1.0f};
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
	mSprite->Position = Point<float>{10, 10};
}

void Snake::Update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback)
{
    Entity::Update(screenWidth, screenHeight);

	auto const newX = static_cast<int>(mSprite->Position.X + mSprite->Velocity.x + SCREEN_SIZE) % SCREEN_SIZE;
	auto const newY = static_cast<int>(mSprite->Position.Y + mSprite->Velocity.y + SCREEN_SIZE) % SCREEN_SIZE;

	if (CheckCollision(newX, newY)) {
		gameCallback->GoToState(GameState::GameOver);
	}
	else {
		mSprite->Position.X = newX;
		mSprite->Position.Y = newY;

		mTrail.push_back( 
			Point<int>{
				static_cast<int>(mSprite->Position.X), 
				static_cast<int>(mSprite->Position.Y)}
		);
		while (mTrail.size() > mTail) {
			mTrail.pop_front();
		}
	}
}

void Snake::HandleInput(shared_ptr<IInputManager> input)
{
	if (mSprite->Velocity.x == 0) {
		if (input->IsKeyDown(37)) {
			mSprite->Velocity = Utilities::Vector2{-1.0f, 0.0f};
		}
		if (input->IsKeyDown(39)) {
			mSprite->Velocity = Utilities::Vector2{1.0f, 0.0f};
		}
	}
	if (mSprite->Velocity.y == 0) {
		if (input->IsKeyDown(40)) {
			mSprite->Velocity = Utilities::Vector2{0.0f, 1.0f};
		}
		if (input->IsKeyDown(38)) {
			mSprite->Velocity = Utilities::Vector2{0.0f, -1.0f};
		}
	}
}

void Snake::Draw(shared_ptr<ISpriteRenderer> renderer) {
	for (auto const& body : mTrail)
	{
        renderer->DrawSprite(mSprite, Point<float>{
			static_cast<float>(body.X * mScreenWidth / SCREEN_SIZE), 
			static_cast<float>(body.Y * mScreenHeight / SCREEN_SIZE)});
    }
}
