#include "Entity.h"
#include "utilities/MathHelper.h"
#include "textures/Texture2D.h"
#include "renderer/Sprite.h"
#include "game/GameDefines.h"

using std::make_shared;
using Utilities::Point;
using Engine::Texture2D;
using Engine::Sprite;

Entity::Entity(Point position)
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
    mSprite->Width = screenWidth / SCREEN_SIZE - 1;
    mSprite->Height = screenHeight / SCREEN_SIZE - 1;

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
}
