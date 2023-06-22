#include "Player.hpp"
#include "sprites/AnimatedSprite.hpp"
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Player::Player()
    : posX(0)
    , posY(0)
{
    printf("[Player::constructor]\n");
    setFrame(4);
    Animation idle;
    idle.loop = true;
    idle.frames = {
        AnimationFrame{4, 100*1000},
        AnimationFrame{4, 100*1000},
    };
    mSprite->animations["idle"] = idle;

    Animation left;
    left.loop = true;
    left.frames = {
        AnimationFrame{8, 100*1000}, 
        AnimationFrame{9, 100*1000},
        AnimationFrame{10, 100*1000},
    };
    mSprite->animations["left"] = left;

    Animation right;
    right.loop = true;
    right.frames = {
        AnimationFrame{7, 100*1000}, 
        AnimationFrame{12, 100*1000},
        AnimationFrame{13, 100*1000},
    };
    mSprite->animations["right"] = right;

    Animation down;
    down.loop = true;
    down.frames = {
        AnimationFrame{4, 100*1000}, 
        AnimationFrame{14, 100*1000},
        AnimationFrame{15, 100*1000},
    };
    mSprite->animations["down"] = down;

    Animation up;
    up.loop = true;
    up.frames = {
        AnimationFrame{6, 100*1000},
        AnimationFrame{11, 100*1000},
    };
    mSprite->animations["up"] = up;


    mSprite->play("idle");
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
    if(deltaY != 0) {
        mSprite->play(deltaY > 0 ? "up" : "down");
	} else if(deltaX != 0) {
        mSprite->play(deltaX > 0 ? "right" : "left");
	}

    isMoving = true;
    MoveableObject::move(deltaX, deltaY, [&](){
        mSprite->isPlaying = false;
        isMoving = false;
    });
}

void Player::update(shared_ptr<IStepTimer> timer)
{
    mSprite->update(timer);
}
