#include "Apple.h"
#include "game/GameDefines.h"
#include "rendering/ISpriteRenderer.h"
#include "rendering/Sprite.h"

using std::shared_ptr;
using Utilities::Vector2;
using Engine::ISpriteRenderer;

Apple::Apple(Vector2 position)
    : Entity(position)
    , mScreenPositionX(0.0f)
    , mScreenPositionY(0.0f)
{ }

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

void Apple::Reset() {
	auto x = static_cast<float>(std::rand() % SCREEN_SIZE);
	auto y = static_cast<float>(std::rand() % SCREEN_SIZE);
	mSprite->Position = Vector2(x, y);
}
