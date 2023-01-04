#include "Apple.h"
#include "game/GameDefines.h"
#include "renderers/ISpriteRenderer.h"
#include "renderers/Sprite.h"
#include "Snake.h"
#include "PointCollider.h"
#include <ctime>

using std::shared_ptr;
using Utilities::Point;
using Engine::ISpriteRenderer;

Apple::Apple(Point<int> position)
    : Entity(position)
    , mScreenPositionX(0.0f)
    , mScreenPositionY(0.0f)
{ 
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Apple::draw(std::shared_ptr<ISpriteRenderer> renderer) {
    renderer->drawSprite(mSprite, Point<float>{mScreenPositionX, mScreenPositionY});
}

void Apple::update(int screenWidth, int screenHeight)
{
    Entity::update(screenWidth, screenHeight);

    mScreenPositionX = mSprite->position.x * screenWidth / SCREEN_SIZE;
    mScreenPositionY = mSprite->position.y * screenHeight / SCREEN_SIZE;
}

void Apple::reset(std::shared_ptr<Snake> snake, std::shared_ptr<PointCollider> collider) {
    Point<int> newPosition{0, 0};
    bool collide;
    do {
        collide = false;
        auto const x = std::rand() % SCREEN_SIZE;
        auto const y = std::rand() % SCREEN_SIZE;
        newPosition = Point<int>{x, y};
        for(auto const& snakeBody: snake->mTrail) {
            if(collider->collides(newPosition, snakeBody)) {
                collide = true;
            }
        }
    } while(collide);
	mSprite->position = Point<float>{
        static_cast<float>(newPosition.x), 
        static_cast<float>(newPosition.y)
    };
}
