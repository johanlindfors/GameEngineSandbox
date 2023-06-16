#include "Player.hpp"
#include "resources/IResourceManager.hpp"
#include "utilities/IOC.hpp"
#include "renderers/SpriteRenderer.hpp"
#include "renderers/Sprite.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Player::Player()
{

}

Player::~Player()
{

}

void Player::initialize()
{
    auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
    mSprite = make_shared<Engine::Sprite>();
    mSprite->texture = resourceManager->getTexture( "tiles.png" );
    mSprite->size = { 256.0f, 256.0f };
}

void Player::update(shared_ptr<IStepTimer> timer)
{

}

void Player::draw(shared_ptr<IRenderer> renderer)
{
    auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {
        spriteRenderer->drawSprite(mSprite);
    }
}