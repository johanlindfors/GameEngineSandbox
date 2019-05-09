#include "Apple.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "renderer/Sprite.h"
#include "Snake.h"
#include "VectorCollider.h"
#include <ctime>

using std::shared_ptr;
using Utilities::Vector2;
using Engine::ISpriteRenderer;

Apple::Apple(Vector2 position)
    : Entity(position)
    , mScreenPositionX(0.0f)
    , mScreenPositionY(0.0f)
{ 
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

void Apple::Draw(std::shared_ptr<ISpriteRenderer> renderer) {
    auto sprite = std::make_shared<Engine::Sprite>(*mSprite);
    sprite->Position = Vector2(mScreenPositionX, mScreenPositionY);
    renderer->DrawSprite(sprite);
}

void Apple::Update(int screenWidth, int screenHeight)
{
    Entity::Update(screenWidth, screenHeight);

    mScreenPositionX = mSprite->Position.m[0] * screenWidth / SCREEN_SIZE;
    mScreenPositionY = mSprite->Position.m[1] * screenHeight / SCREEN_SIZE;
}

void Apple::Reset(std::shared_ptr<Snake> snake, std::shared_ptr<VectorCollider> collider) {
    Vector2 newPosition(0.0f, 0.0f);
    bool collide;
    do {
        collide = false;
        auto x = static_cast<float>(std::rand() % SCREEN_SIZE);
        auto y = static_cast<float>(std::rand() % SCREEN_SIZE);
        newPosition = Vector2(x, y);
        for(Vector2 const& snakeBody: snake->mTrail) {
            if(collider->Collides(newPosition, snakeBody)) {
                collide = true;
            }
        }
    } while(collide);
	mSprite->Position = newPosition;
}
