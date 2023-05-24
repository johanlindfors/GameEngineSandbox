#include "Clouds.h"
#include "utilities/IStepTimer.h"
#include "renderers/SpriteRenderer.h"
#include "renderers/Sprite.h"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Clouds::Clouds(Point<float> position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mClouds(make_shared<Sprite>())
    , mCloudsBackground(make_shared<Sprite>())
{
    mClouds->position = Point<float>{position.x, position.y + 200};
    mClouds->size = { 351.0, 33.0 };
    // mClouds->offset = 5;

    mCloudsBackground->position = Point<float>{position.x, position.y};
    mCloudsBackground->size = { 288.0, 200.0 };
    // mCloudsBackground->offset = 18;   
}

void Clouds::initializeSprite()
{
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto texture = resourceManager->getTexture("atlas.png");
	mClouds->texture = texture;
    mCloudsBackground->texture = texture;
    mClouds->offset = {
        1.0f / 512.0f, (512.0f - 103.0f) / 512.0f,
        351.0f / 512.0f, 33.0f / 512.0f
    }; // 1, 70, 352, 103
    mCloudsBackground->offset = {
        1.0f / 512.0f, (512.0f - 103.0f) / 512.0f,
        1.0f / 512.0f, 1.0f / 512.0f

    }; // 1, 102, 2, 103
}

void Clouds::update(shared_ptr<IStepTimer> timer)
{
    mPosition.x += (mVelocity.x * timer->getElapsedMilliSeconds());
    if(mPosition.x <= -351.0) {
        mPosition.x += 351.0;
    }
}

void Clouds::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);    
    spriteRenderer->drawSprite(mClouds, mPosition);
    spriteRenderer->drawSprite(mClouds, Point<float>{mPosition.x + 351, mPosition.y});
    spriteRenderer->drawSprite(mCloudsBackground, Point<float>{0, mPosition.y - 200});
}
