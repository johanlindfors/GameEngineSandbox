#include "Bird.h"
#include "game/GameDefines.h"
#include "renderers/SpriteRenderer.h"
#include "input/IInputManager.h"
#include "utilities/ITweenEngine.h"
#include "utilities/MathHelper.h"
#include "renderers/Sprite.h"
#include "utilities/IStepTimer.h"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Bird::Bird(Point<float> position)
    : IPhysicsBody(position)
	, bounds(Circle( position.x+16, position.x+12, 12 ))
	, AABB(Utilities::Rectangle<float>( 0.0f, 0.0f, 0.0f, 0.0f ))
	, isKilled(false)
	, mCounter( 0 )
	, mAnimationCounter( 0 )
	, mFramesPerAnimation( 4 )
	, mSprite(make_shared<Sprite>())
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	, mDebugSprite(make_shared<Sprite>())
#endif
{
    mSprite->size = { 33.0f, 24.0f };
}

void Bird::initializeSprite() {
	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto texture = resourceManager->getTexture("atlas.png");
	mSprite->texture.textureIndex = texture.textureIndex;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	mDebugSprite->texture.textureIndex = texture.textureIndex;
#endif
	mSprite->offset = {
		1.0f / 512.0f + (34.0f / 512.0f * mAnimationCounter), (512.0f - 25.0f) / 512.0f,
		34.0f / 512.0f, 24.0f / 512.0f
	};

}

void Bird::reset() {
	position = Point<float>{ 85.0f, SCREEN_HEIGHT/2.0f - 12.0f };
	velocity = Vector2{ 0.0f, 0.0f };
	mSprite->rotation = 0.0f;
	mAnimationCounter = 0;
	mCounter = 0;
	isKilled = false;
	isAlive = true;
	allowGravity = false;
}

void Bird::update(shared_ptr<IStepTimer> timer)
{
	if(isAlive) {
		if( position.y >= 465.0f ){
			position.y = 465.0f;
		}
		if( mCounter++ >= mFramesPerAnimation ) {
			mSprite->offset = {
				1.0f / 512.0f + (34.0f / 512.0f * mAnimationCounter), (512.0f - 25.0f) / 512.0f,
				34.0f / 512.0f, 24.0f / 512.0f
			};
			mCounter = 0;
			mAnimationCounter = (mAnimationCounter + 1) % 3;
		}

		if (allowGravity && mSprite->rotation > -90 && isAlive)
		{
			mSprite->rotation -= (160.0f * timer->getElapsedMilliSeconds() / 1000.0f);
		}

		AABB = Utilities::Rectangle<float>(position.x,
						position.y,
						mSprite->size.width,
						mSprite->size.height);
		bounds = Circle(position.x + mSprite->size.width/2.0f,
						position.y + mSprite->size.height/2.0f,
						12);
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		mDebugSprite->position = Point<float>{AABB.position.x, AABB.position.y};
		mDebugSprite->offset = {
			1.0f / 512.0f, (512.0f - 371.0f) / 512.0f,
			1.0f / 512.0f, 1.0f / 512.0f
		}; // 1, 364, 8, 371
		mDebugSprite->size = AABB.size;
#endif
	}
}

void Bird::flap()
{
	if(isAlive && !isKilled) {
		allowGravity = true;
		velocity.y = 400;

		auto tweenEngine = IOCContainer::instance().resolve<ITweenEngine>();
		tweenEngine->add(static_cast<int>(mSprite->rotation), [&](int value)
		{
 			mSprite->rotation = static_cast<float>(value);
		}, 40, 100, false);
	}
}

void Bird::collideWithPipe()
{
	isKilled = true;
}

void Bird::draw(shared_ptr<IRenderer> renderer) {
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer) {
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		spriteRenderer->drawSprite(mDebugSprite, position);
#endif
		spriteRenderer->drawSprite(mSprite, position);
	}
}
