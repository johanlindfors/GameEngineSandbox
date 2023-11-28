#include "Ground.hpp"
#include "utilities/IStepTimer.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "sprites/Sprite.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Ground::Ground(Point<float> position, Vector2 velocity)
    : mPosition(position),
    mVelocity(velocity),
    mGround(vector<Point<float>>()),
    mGroundSprite(make_shared<Sprite>()),
    mGroundBackgroundSprite(make_shared<Sprite>()),
    mIsRunning(true),
    mGroundBackgroundOffset(0),
    mGroundOffset(0),

#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    mGroundDebugSprite(make_shared<Sprite>()),
#endif
    ICollidable::ICollidable(position)
{
    for (size_t i = 0; i < 14; i++)
    {
        auto ground = Point<float>{position.x + i * 23, position.y};
        mGround.push_back(ground);
    }

    mGroundSprite->size = {23.0, 26.0f};

    mGroundBackgroundSprite->position = Point<float>{position.x, position.y - 200};
    mGroundBackgroundSprite->size = {288.0, 200.0f};

    AABB.size = {288.0, 105.0};
    AABB.position.y = 0.0f;

#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    mGroundDebugSprite->size = {288.0, 105.0f};
    mGroundDebugSprite->offset = {
        1.0f / 512.0f, (512.0f - 371.0f) / 512.0f,
        1.0f / 512.0f, 1.0f / 512.0f}; // 1, 364, 8, 371
#endif
}

void Ground::initializeSprite()
{
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    auto texture = resourceManager->getTexture("atlas.png");
    mGroundSprite->texture = texture;
    mGroundBackgroundSprite->texture = texture;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    mGroundDebugSprite->texture = texture;
#endif
    mGroundSprite->offset = {
        108.0f / 512.0f, (512.0f - 27.0f) / 512.0f,
        23.0f / 512.0f, 26.0f / 512.0f}; // 108, 1, 131, 27;

    mGroundBackgroundSprite->offset = {
        109.0f / 512.0f, (512.0f - 27.0f) / 512.0f,
        1.0f / 512.0f, 1.0f / 512.0f}; // 108, 26, 109, 27
}

void Ground::update(shared_ptr<IStepTimer> timer)
{
    if (!mIsRunning)
        return;
    for (auto &ground : mGround)
    {
        ground.x += (mVelocity.x * timer->getElapsedMilliSeconds());
        if (ground.x <= -30)
        {
            ground.x += 14 * 23;
        }
    }
}

void Ground::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
    spriteRenderer->drawSprite(mGroundBackgroundSprite, mGroundBackgroundSprite->position);
    for (const auto &position : mGround)
    {
        spriteRenderer->drawSprite(mGroundSprite, position);
    }
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
    spriteRenderer->drawSprite(mGroundDebugSprite);
#endif
}
