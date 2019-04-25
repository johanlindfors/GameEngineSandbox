#include "Snake.h"
#include "GameDefines.h"
#include "sprites/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "MathHelper.h"
#include "sprites/Sprite.h"

using std::shared_ptr;
using Utilities::Vector2;
using Engine::ISpriteRenderer;
using Engine::IInputManager;

Snake::Snake(Vector2 position)
    : Entity(position)
{
    mTail = INITIAL_TAIL;	
    mSprite->Velocity = Vector2(0.0f, 1.0f);
}

bool Snake::CheckCollision(int x, int y) {
    for (auto const& body : mTrail) {
        if (body.m[0] == x && body.m[1] == y) {
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
	mSprite->Position = Vector2(10, 10);
}

void Snake::Update(int screenWidth, int screenHeight)
{
    Entity::Update(screenWidth, screenHeight);
    mSprite->Position.m[0] = static_cast<int>(mSprite->Position.m[0] + mSprite->Velocity.m[0] + SCREEN_SIZE) % SCREEN_SIZE;
    mSprite->Position.m[1] = static_cast<int>(mSprite->Position.m[1] + mSprite->Velocity.m[1] + SCREEN_SIZE) % SCREEN_SIZE;

    mTrail.push_back({ mSprite->Position.m[0] * screenWidth/ SCREEN_SIZE, mSprite->Position.m[1] * screenHeight / SCREEN_SIZE });
    while (mTrail.size() > mTail) {
        mTrail.pop_front();
    }
}

void Snake::HandleInput(shared_ptr<IInputManager> input)
{
    if (input->IsKeyDown(40)) {
        mSprite->Velocity = Utilities::Vector2(0.0f, 1.0f);
    }
    if (input->IsKeyDown(38)) {
        mSprite->Velocity = Utilities::Vector2(0.0f, -1.0f);
    }
    if (input->IsKeyDown(37)) {
        mSprite->Velocity = Utilities::Vector2(-1.0f, 0.0f);
    }
    if (input->IsKeyDown(39)) {
        mSprite->Velocity = Utilities::Vector2(1.0f, 0.0f);
    }
}

void Snake::Draw(shared_ptr<ISpriteRenderer> renderer) {
    for (auto const& body : mTrail)
    {
		auto sprite = std::make_shared<Engine::Sprite>(*mSprite);
        sprite->Position = body;
        renderer->DrawSprite(sprite);
    }
}
