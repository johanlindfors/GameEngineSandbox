#include "Entity.h"
#include "utilities/MathHelper.h"
#include "resources/Texture2D.h"
#include "renderers/Sprite.h"
#include "game/GameDefines.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Entity::Entity(Point<int> position)
    : mSprite(std::make_shared<Sprite>())
	, mScreenWidth(0)
	, mScreenHeight(0)
{
    mSprite->Position = Point<float>{position.X, position.Y};
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
