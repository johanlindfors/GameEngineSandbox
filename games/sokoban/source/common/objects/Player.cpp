#include "Player.hpp"
#include "sprites/AnimatedSprite.hpp"
#include "game/GameDefines.hpp"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Player::Player()
    : posX(0)
    , posY(0)
{
    printf("[Player::constructor]\n");
    
    auto sprite = make_shared<AnimatedSprite>();
    sprite->texture = IOCContainer::instance().resolve<IResourceManager>()->getTexture( TILES );
    sprite->size = { TILE_SIZE, TILE_SIZE };
    sprite->tileSize = { 128, 128 };

    Animation idle;
    idle.loop = true;
    idle.frames = {
        AnimationFrame{4, 500*1000},
        AnimationFrame{4, 500*1000},
    };
    sprite->animations["idle"] = idle;

    Animation left;
    left.loop = true;
    left.frames = {
        AnimationFrame{8, 100*1000}, 
        AnimationFrame{9, 100*1000},
        AnimationFrame{10, 100*1000},
    };
    sprite->animations["left"] = left;

    Animation right;
    right.loop = true;
    right.frames = {
        AnimationFrame{7, 100*1000}, 
        AnimationFrame{12, 100*1000},
        AnimationFrame{13, 100*1000},
    };
    sprite->animations["right"] = right;

    Animation down;
    down.loop = true;
    down.frames = {
        AnimationFrame{4, 100*1000}, 
        AnimationFrame{14, 100*1000},
        AnimationFrame{15, 100*1000},
    };
    sprite->animations["down"] = down;

    Animation up;
    up.loop = true;
    up.frames = {
        AnimationFrame{6, 100*1000},
        AnimationFrame{11, 100*1000},
    };
    sprite->animations["up"] = up;

    sprite->play("idle");
    mSprite = sprite;
}

void Player::initialize(int x, int y)
{
    posX = x;
    posY = y;
    mSprite->position = {
        static_cast<float>(x * TILE_SIZE), 
        static_cast<float>(y * TILE_SIZE)
    };
}

void Player::move(int deltaX, int deltaY)
{
    auto sprite = static_pointer_cast<AnimatedSprite>(mSprite);
    if(deltaY != 0) {
        sprite->play(deltaY > 0 ? "up" : "down");
	} else if(deltaX != 0) {
        sprite->play(deltaX > 0 ? "right" : "left");
	}

    isMoving = true;
    MoveableObject::move(deltaX, deltaY, [&](){
        sprite->isPlaying = false;
        isMoving = false;
        mSprite = sprite;
    });
    mSprite = sprite;
}

void Player::update(shared_ptr<IStepTimer> timer)
{
    auto sprite = static_pointer_cast<AnimatedSprite>(mSprite);
    sprite->update(timer);
}
