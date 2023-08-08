#include "Snake.hpp"
#include "game/GameDefines.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "input/IInputManager.hpp"
#include "utilities/MathHelper.hpp"
#include "sprites/Sprite.hpp"
#include "game/IGameStateCallback.hpp"
#include <algorithm>

using namespace std;
using namespace Engine;
using namespace Utilities;

Snake::Snake(Point<int> position)
    : Entity(position)
{
    mBodyLength = INITIAL_TAIL;

	mHead.position = position;
	mHead.direction = Point<int>{0, 1};

	mTail.position = position;
	mTail.direction = Point<int>{0, 1};
}

bool Snake::checkCollision(int x, int y) {
    for (auto const& body : mBody) {
        if (body.position.x == x && body.position.y == y) {
            return true;
        }
    }
    return false;
}

void Snake::increaseLength() {
	mBodyLength += 1;
}

void Snake::reset() {
	mBodyLength = INITIAL_TAIL;
	mSprite->position = Point<float>{10, 10};
}

void Snake::update(int screenWidth, int screenHeight, IGameStateCallback* gameCallback)
{
    Entity::update(screenWidth, screenHeight);

	// Update head
	auto oldPosition = mHead.position;

	mHead.position.x = static_cast<int>(mHead.position.x + mHead.direction.x + SCREEN_SIZE) % SCREEN_SIZE;
	mHead.position.y = static_cast<int>(mHead.position.y + mHead.direction.y + SCREEN_SIZE) % SCREEN_SIZE;

	// Add "previous" head position in body list
	mBody.push_back(BodyPart { oldPosition, mHead.direction });
	
	// Update tail
	if(mBodyLength > 0) {
		mBodyLength -= 1;
	} else {
		std::list<BodyPart>::iterator iter = std::find_if(mBody.begin(), mBody.end(), [&](const BodyPart& part) {
			return part.position.x == mTail.position.x && part.position.y == mTail.position.y;
		});
		if(mBody.end() != iter) {
			mTail.position.x = static_cast<int>(mTail.position.x + iter->direction.x + SCREEN_SIZE) % SCREEN_SIZE;
			mTail.position.y = static_cast<int>(mTail.position.y + iter->direction.y + SCREEN_SIZE) % SCREEN_SIZE;

			mBody.erase(iter);
		}
	}

	// check for collision with own body
	if (checkCollision(mHead.position.x, mHead.position.y)) {
		gameCallback->goToState(GameState::GameOver);
	}
}

void Snake::handleInput(shared_ptr<IInputManager> input)
{
	if (mHead.direction.x == 0) {
		if (input->isKeyDown(37)) {
			mHead.direction = Utilities::Point<int>{-1, 0};
		}
		if (input->isKeyDown(39)) {
			mHead.direction = Utilities::Point<int>{1, 0};
		}
	}
	if (mHead.direction.y == 0) {
		if (input->isKeyDown(40)) {
			mHead.direction = Utilities::Point<int>{0, -1};
		}
		if (input->isKeyDown(38)) {
			mHead.direction = Utilities::Point<int>{0, 1};
		}
	}
}

void Snake::draw(shared_ptr<SpriteRenderer> renderer) {
	for (auto const& body : mBody)
	{
        renderer->drawSprite(mSprite, Point<float>{
			static_cast<float>(body.position.x * mScreenWidth / SCREEN_SIZE), 
			static_cast<float>(body.position.y * mScreenHeight / SCREEN_SIZE)});
    }
}
