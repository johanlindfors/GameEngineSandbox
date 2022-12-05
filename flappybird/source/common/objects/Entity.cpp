#include "Entity.h"
#include "utilities/MathHelper.h"
#include "textures/Texture2D.h"
#include "renderer/Sprite.h"
#include "game/GameDefines.h"
#include "utilities/IStepTimer.h"

using std::make_shared;
using std::shared_ptr;
using Utilities::Vector2;
using Utilities::IStepTimer;
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

void Entity::Update(shared_ptr<IStepTimer> timer)
{
    //printf("Elpased %u\n", timer->GetElapsedMilliSeconds());
}
