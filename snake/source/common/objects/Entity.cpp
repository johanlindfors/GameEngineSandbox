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
    mSprite->position = Point<float>{
        static_cast<float>(position.x), 
        static_cast<float>(position.y)
    };
}

void Entity::setTexture(Texture2D texture) 
{
    mSprite->texture = texture;
}

void Entity::update(int screenWidth, int screenHeight)
{
    mSprite->width = screenWidth / SCREEN_SIZE - 1;
    mSprite->height = screenHeight / SCREEN_SIZE - 1;

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
}
