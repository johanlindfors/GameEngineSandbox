#include "Entity.h"

using Utilities::Vector2;
using Engine::Texture2D;

Entity::Entity(Vector2 position)
{
    mSprite.Position = position;
}

void Entity::SetTexture(Texture2D texture) 
{
    mSprite.Texture = texture;
}

void Entity::Update(int screenWidth, int screenHeight)
{
    mSprite.Width = screenWidth / SCREEN_SIZE - 1;
    mSprite.Height = screenHeight / SCREEN_SIZE - 1;
}
