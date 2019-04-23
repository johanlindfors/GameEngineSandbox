#include "Apple.h"
#include "GameDefines.h"

using std::shared_ptr;
using Utilities::Vector2;
using Engine::ISpriteRenderer;

Apple::Apple(Vector2 position)
    : Entity(position)
    , mScreenPosition(Utilities::Vector2(0.0f, 0.0f))
{ }

void Apple::Draw(std::shared_ptr<ISpriteRenderer> renderer) {
    auto sprite = mSprite;
    sprite->Position = mScreenPosition;
    renderer->DrawSprite(sprite);
}

void Apple::Update(int screenWidth, int screenHeight)
{
    Entity::Update(screenWidth, screenHeight);

    mScreenPosition = Vector2({ mSprite->Position.m[0] * screenWidth / SCREEN_SIZE, mSprite->Position.m[1] * screenHeight / SCREEN_SIZE });
}
