#include "Player.hpp"
#include "renderers/TiledSprite.hpp"
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
    idle.numberOfFrames = 2;
    idle.loop = true;
    idle.frames = {
        AnimationFrame{4, 100*1000},
        AnimationFrame{4, 100*1000},
    };
    mTiledSprite->animations["idle"] = idle;

    Animation left;
    left.numberOfFrames = 3;
    left.loop = true;
    left.frames = {
        AnimationFrame{8, 100*1000}, 
        AnimationFrame{9, 100*1000},
        AnimationFrame{10, 100*1000},
    };
    mTiledSprite->animations["left"] = left;

    Animation right;
    right.numberOfFrames = 3;
    right.loop = true;
    right.frames = {
        AnimationFrame{7, 100*1000}, 
        AnimationFrame{12, 100*1000},
        AnimationFrame{13, 100*1000},
    };
    mTiledSprite->animations["right"] = right;

    Animation down;
    down.numberOfFrames = 3;
    down.loop = true;
    down.frames = {
        AnimationFrame{4, 100*1000}, 
        AnimationFrame{14, 100*1000},
        AnimationFrame{15, 100*1000},
    };
    mTiledSprite->animations["down"] = down;

    Animation up;
    up.numberOfFrames = 2;
    up.loop = true;
    up.frames = {
        AnimationFrame{6, 100*1000},
        AnimationFrame{11, 100*1000},
    };
    mTiledSprite->animations["up"] = up;


    mTiledSprite->play("idle");
}

void Player::initialize(int x, int y)
{
    posX = x;
    posY = y;
    mTiledSprite->position = { 
        static_cast<float>(x * TILE_SIZE), 
        static_cast<float>(y * TILE_SIZE)
    };
}

void Player::move(int deltaX, int deltaY)
{
    if(deltaY != 0) {
        mTiledSprite->play(deltaY > 0 ? "up" : "down");
	// 	mPlayer->setFrame(deltaY == 1 ? 6 : 4);
	} else if(deltaX != 0) {
        mTiledSprite->play(deltaX > 0 ? "right" : "left");
	// 	mPlayer->setFrame(deltaX == 1 ? 7 : 8);
	}

    isMoving = true;
    //mTiledSprite->resume();
    MoveableObject::move(deltaX, deltaY, [&](){
        mTiledSprite->isPlaying = false;
        isMoving = false;
    });
}

void Player::update(shared_ptr<IStepTimer> timer)
{
    mTiledSprite->update(timer);
}
