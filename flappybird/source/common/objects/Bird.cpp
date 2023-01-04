#include "Bird.h"
#include "game/GameDefines.h"
#include "renderers/ISpriteRenderer.h"
#include "input/IInputManager.h"
#include "utilities/ITweenEngine.h"
#include "utilities/MathHelper.h"
#include "renderers/Sprite.h"
#include "utilities/IStepTimer.h"
#include "utilities/IOC.hpp"

using namespace std;
using namespace Engine;
using namespace Utilities;

Bird::Bird(Point<float> position)
    : IPhysicsBody(position)
	, bounds(Circle(position.x+16, position.x+12, 12))
	, AABB(Utilities::Rectangle(0, 0, 0, 0))
	, isKilled(false)
	, mAnimationCounter(0)
	, mFramesPerAnimation(4)
	, mSprite(make_shared<Sprite>())
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	, mDebugSprite(make_shared<Sprite>())
#endif
{
    mSprite->width = 33;
	mSprite->height = 24;
}

void Bird::reset() {
	position = Point<float>{85.0f, SCREEN_HEIGHT/2.0f-12};
	velocity = Vector2{0.0f, 0.0f};
	mSprite->rotation = 0;
	mAnimationCounter = 0;
	isKilled = false;
	isAlive = true;
	allowGravity = false;
}

void Bird::update(shared_ptr<IStepTimer> timer)
{
	if(isAlive) {
		if(position.y >=465){
			position.y = 465;
		}
		if(mAnimationCounter++ >= mFramesPerAnimation) {
			auto offset = mSprite->offset;
			offset++;
			offset %= 3;
			mSprite->offset = offset;
			mAnimationCounter = 0;
		}

		if (allowGravity && mSprite->rotation > -90 && isAlive)
		{
			mSprite->rotation -= (160.0f * timer->getElapsedMilliSeconds() / 1000.0f);
		}

		AABB = Utilities::Rectangle(position.x,
						position.y,
						mSprite->width,
						mSprite->height);
		bounds = Circle(position.x + mSprite->width/2,
						position.y + mSprite->height/2,
						12);
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		mDebugSprite->position = Point<float>(AABB.position.x, AABB.position.y);
		mDebugSprite->offset = 22;
		mDebugSprite->width = AABB.width;
		mDebugSprite->height = AABB.height;
#endif
	}
}

void Bird::flap()
{
	if(isAlive && !isKilled) {
		allowGravity = true;
		velocity.y = 400;

		auto tweenEngine = IOCContainer::instance().resolve<ITweenEngine>();
		tweenEngine->add(mSprite->rotation, [&](int value)
		{
 			mSprite->rotation = value;
		}, 40, 100, false);
	}
}

void Bird::collideWithPipe()
{
	isKilled = true;
}

void Bird::draw(shared_ptr<ISpriteRenderer> renderer) {
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	renderer->drawSprite(mDebugSprite, position);
#endif
	renderer->drawSprite(mSprite, position);
}
