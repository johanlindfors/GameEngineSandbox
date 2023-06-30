#include "Skyline.hpp"
#include "utilities/IStepTimer.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "sprites/Sprite.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Skyline::Skyline(Point<float> position, Vector2 velocity)
    : mSprite(make_shared<Sprite>())
    , mVelocity(velocity)
    , mSkyline(vector<Point<float>>())
    , mTextureOffset(0)
{
    mSprite->size = { 86.0f, 42.0f };
    // mSprite->offset = 4;

    for (size_t i = 0; i < 6; i++)
    {
        auto point = Point<float>{position.x + i * 86, position.y};
        mSkyline.push_back(point);
    }
}

void Skyline::initializeSprite()
{
   	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto texture = resourceManager->getTexture("atlas.png");
	mSprite->texture = texture;
    mSprite->offset = {
        1.0f / 512.0f, (512.0f - 68.0f) / 512.0f,
        86.0f / 512.0f, 42.0f / 512.0f
    }; // 1, 26, 87, 68
}

void Skyline::update(shared_ptr<IStepTimer> timer)
{
    for(auto & position: mSkyline) {
        position.x += (mVelocity.x * timer->getElapsedMilliSeconds());
        if(position.x < -100.0) {
            position.x += 6 * 86;
        } 
    }
}

void Skyline::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
    for(auto const& position: mSkyline) {
        spriteRenderer->drawSprite(mSprite, position);
    }
}
