#include "Snake.hpp"
#include "game/GameDefines.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "utilities/MathHelper.hpp"
#include "renderers/Sprite.hpp"
#include "game/IGameStateCallback.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Snake::Snake(Point<int> position)
    : Entity(position)
{
    mTail = INITIAL_TAIL;	
    mSprite->velocity = Vector2{0.0f, 1.0f};
}

bool Snake::checkCollision(int x, int y) {
    for (auto const& body : mTrail) {
        if (body.x == x && body.y == y) {
            return true;
        }
    }
    return false;
}

void Snake::increaseLength() {
	mTail += 1;
}

void Snake::reset() {
	mTail = INITIAL_TAIL;
	mSprite->position = Point<float>{10, 10};
}

void Snake::update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback)
{
    Entity::update(screenWidth, screenHeight);

	auto const newX = static_cast<int>(mSprite->position.x + mSprite->velocity.x + SCREEN_SIZE) % SCREEN_SIZE;
	auto const newY = static_cast<int>(mSprite->position.y + mSprite->velocity.y + SCREEN_SIZE) % SCREEN_SIZE;

	if (checkCollision(newX, newY)) {
		gameCallback->goToState(GameState::GameOver);
	}
	else {
		mSprite->position.x = newX;
		mSprite->position.y = newY;

		mTrail.push_back( 
			Point<int>{
				static_cast<int>(mSprite->position.x), 
				static_cast<int>(mSprite->position.y)}
		);
		while (mTrail.size() > mTail) {
			mTrail.pop_front();
		}
	}
}

void Snake::handleInput(shared_ptr<IInputManager> input)
{
	if (mSprite->velocity.x == 0) {
		if (input->isKeyDown(37)) {
			mSprite->velocity = Utilities::Vector2{-1.0f, 0.0f};
		}
		if (input->isKeyDown(39)) {
			mSprite->velocity = Utilities::Vector2{1.0f, 0.0f};
		}
	}
	if (mSprite->velocity.y == 0) {
		if (input->isKeyDown(40)) {
			mSprite->velocity = Utilities::Vector2{0.0f, -1.0f};
		}
		if (input->isKeyDown(38)) {
			mSprite->velocity = Utilities::Vector2{0.0f, 1.0f};
		}
	}
}

void Snake::draw(shared_ptr<SpriteRenderer> renderer) {
	for (auto const& body : mTrail)
	{
        renderer->drawSprite(mSprite, Point<float>{
			static_cast<float>(body.x * mScreenWidth / SCREEN_SIZE), 
			static_cast<float>(body.y * mScreenHeight / SCREEN_SIZE)});
    }
}
