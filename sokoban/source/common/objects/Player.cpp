#include "Player.hpp"
#include "renderers/Sprite.hpp"
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
    isMoving = true;
    MoveableObject::move(deltaX, deltaY, [&](){
        isMoving = false;
    });
}
