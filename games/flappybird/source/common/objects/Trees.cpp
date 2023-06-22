#include "Trees.hpp"
#include "utilities/IStepTimer.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Sprite.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Trees::Trees(Point<float> position, Vector2 velocity)
    : mPosition(position)
    , mVelocity(velocity)
    , mTrees(make_shared<Sprite>())
    , mTreesBackground(make_shared<Sprite>())
    , mCloudsBackgroundOffset(0)
    , mCloudsOffset(0)
{
    mTrees->size = { 415.0f, 32.0f };
    // mTrees->offset = 14;

    mTreesBackground->size = { 415.0f, 200.0f };
    // mTreesBackground->offset = 19;   
}

void Trees::initializeSprite()
{
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto texture = resourceManager->getTexture("atlas.png");
	mTrees->texture = texture;
    mTreesBackground->texture = texture;
    mTrees->offset = {
        2.0f / 512.0f, (512.0f - 510.0f) / 512.0f,
        415.0f / 512.0f, 32.0f / 512.0f
    }; // 2, 478, 417, 510
    mTreesBackground->offset = {
        2.0f / 512.0f, 2.0f / 512.0f,
        1.0f / 512.0f, 1.0f / 512.0f
    }; // 2, 509, 3, 510
}

void Trees::update(shared_ptr<IStepTimer> timer)
{
    mPosition.x += (mVelocity.x * timer->getElapsedMilliSeconds());
    if(mPosition.x <= -415.0) {
        mPosition.x += 415.0;
    }
}

void Trees::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
    if(spriteRenderer) {
        spriteRenderer->drawSprite(mTrees, mPosition);
        spriteRenderer->drawSprite(mTrees, Point<float>{mPosition.x + 415, mPosition.y});
        spriteRenderer->drawSprite(mTreesBackground, Point<float>{0, mPosition.y - 200});
    }
}
