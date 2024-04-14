#include "Player.hpp"

// engine
#include "sprites/AnimatedSprite.hpp"
#include "utilities/IOC.hpp"
#include "utilities/Logger.hpp"
#include "resources/IResourceManager.hpp"

// game
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Player::Player()
    : posX(0), posY(0)
{
    debuglog << "[Player::constructor]" << endl;

#if (IS_ANIMATED == true)
    auto sprite = make_shared<AnimatedSprite>();

    Animation idle;
    idle.loop = true;
    idle.frames = {
        AnimationFrame{4, 50 * 1000},
        AnimationFrame{4, 50 * 1000},
    };
    sprite->animations["idle"] = idle;

    Animation left;
    left.loop = true;
    left.frames = {
        AnimationFrame{8, 50 * 1000},
        AnimationFrame{9, 50 * 1000},
        AnimationFrame{10, 50 * 1000},
    };
    sprite->animations["left"] = left;

    Animation right;
    right.loop = true;
    right.frames = {
        AnimationFrame{7, 50 * 1000},
        AnimationFrame{12, 50 * 1000},
        AnimationFrame{13, 50 * 1000},
    };
    sprite->animations["right"] = right;

    Animation down;
    down.loop = true;
    down.frames = {
        AnimationFrame{4, 50 * 1000},
        AnimationFrame{14, 50 * 1000},
        AnimationFrame{15, 50 * 1000},
    };
    sprite->animations["down"] = down;

    Animation up;
    up.loop = true;
    up.frames = {
        AnimationFrame{6, 50 * 1000},
        AnimationFrame{11, 50 * 1000},
    };
    sprite->animations["up"] = up;
#else
    auto sprite = make_shared<TiledSprite>();
#endif
    sprite->texture = IOCContainer::instance().resolve<IResourceManager>()->getTexture(TILES);
    sprite->size = {TILE_SIZE, TILE_SIZE};
    sprite->tileSize = {128, 128};
    sprite->setFrame(4);
    mSprite = static_pointer_cast<Sprite>(sprite);
}

void Player::initialize(int x, int y)
{
    posX = x;
    posY = y;
    mSprite->position = {
        static_cast<float>(x * TILE_SIZE),
        static_cast<float>(y * TILE_SIZE)};
}

void Player::move(int deltaX, int deltaY)
{
#if IS_ANIMATED == true
    auto sprite = static_pointer_cast<AnimatedSprite>(mSprite);
    if (deltaY != 0)
    {
        sprite->play(deltaY > 0 ? "up" : "down");
    }
    else if (deltaX != 0)
    {
        sprite->play(deltaX > 0 ? "right" : "left");
    }
#endif
    isMoving = true;
    MoveableObject::move(deltaX, deltaY, [&]()
                         {
#if IS_ANIMATED == true
        auto sprite = static_pointer_cast<AnimatedSprite>(mSprite);    
        sprite->isPlaying = false;
#endif
        isMoving = false; });
}

void Player::update(shared_ptr<IStepTimer> timer)
{
#if IS_ANIMATED == true
    auto sprite = static_pointer_cast<AnimatedSprite>(mSprite);
    sprite->update(timer);
#endif
}