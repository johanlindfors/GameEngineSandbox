#include "Entity.hpp"
#include "utilities/MathHelper.hpp"
#include "resources/Texture2D.hpp"
#include "sprites/Sprite.hpp"
#include "game/GameDefines.hpp"

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
    mSprite->size = { 
        static_cast<float>(screenWidth / SCREEN_SIZE - 1),
        static_cast<float>(screenHeight / SCREEN_SIZE - 1)
    };

	mScreenWidth = screenWidth;
	mScreenHeight = screenHeight;
}
