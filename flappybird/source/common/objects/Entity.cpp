#include "Entity.h"
#include "MathHelper.h"
#include "textures/Texture2D.h"
#include "renderer/Sprite.h"
#include "game/GameDefines.h"

using std::make_shared;
using Utilities::Vector2;
using Engine::Texture2D;
using Engine::Sprite;

Entity::Entity(Vector2 position)
    : mSprite(std::make_shared<Sprite>())
	, mScreenWidth(0)
	, mScreenHeight(0)
{
    mSprite->Position = position;
}

void Entity::SetTexture(Texture2D texture) 
{
    mSprite->Texture = texture;
}

void Entity::Update(int screenWidth, int screenHeight)
{
    mSprite->Width = screenWidth / SCREEN_WIDTH - 1;
    mSprite->Height = screenHeight / SCREEN_HEIGHT - 1;

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
}
