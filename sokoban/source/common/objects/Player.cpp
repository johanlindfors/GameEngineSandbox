#include "Player.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Sprite.hpp"
#include "game/GameDefines.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Player::Player()
    : posX(0)
    , posY(0)
{
    mFrame = 4;
}

Player::~Player()
{

}

void Player::initialize(int x, int y)
{
    posX = x;
    posY = y;
    mSprite->position = { static_cast<float>(x * TILE_SIZE), static_cast<float>(y * TILE_SIZE)};
}

void Player::update(shared_ptr<IStepTimer> timer)
{
    MoveableObject::update();
}

void Player::draw(shared_ptr<IRenderer> renderer)
{
    MoveableObject::draw(renderer);
}

void Player::move(int deltaX, int deltaY)
{
    MoveableObject::move(deltaX, deltaY);
    posX += deltaX;
    posY += deltaY;
}