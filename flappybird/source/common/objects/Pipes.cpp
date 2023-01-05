#include "Pipes.h"
#include "game/GameDefines.h"
#include "renderers/ISpriteRenderer.h"
#include "utilities/MathHelper.h"
#include "utilities/IStepTimer.h"
#include "game/GameDefines.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Pipes::Pipes(Point<float> position)
	: topPipe(make_shared<Pipe>(position))
	, bottomPipe(make_shared<Pipe>(position))
	, topPipeSprite(make_shared<Sprite>())
	, bottomPipeSprite(make_shared<Sprite>())
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	, topPipeDebugSprite(make_shared<Sprite>())
	, bottomPipeDebugSprite(make_shared<Sprite>())
#endif
	, isAlive(true)
	, hasScored(false)
{
	reset(position);

	topPipe->offset = 16;
	topPipeSprite->offset = 21;
	topPipeSprite->width = topPipe->width;
	
	bottomPipe->offset = 17;
	bottomPipeSprite->offset = 21;
	bottomPipeSprite->width = topPipe->width;
}

void Pipes::reset(Point<float> position)
{
	topPipe->position = Point<float>{position.x, position.y};
	bottomPipe->position = Point<float>{position.x, position.y};

	topPipe->position.y += 400;
	bottomPipe->position.y += 250;

	topPipeSprite->height = 505 - topPipe->position.y - topPipe->height;
	topPipeSprite->position = Point<float>{topPipe->position.x, topPipe->position.y + 25};

	bottomPipeSprite->height = bottomPipe->position.y - 95;
	bottomPipeSprite->position = Point<float>{bottomPipe->position.x, bottomPipe->position.y - bottomPipeSprite->height};

	isAlive = true;
	hasScored = false;
}

void Pipes::update(shared_ptr<IStepTimer> timer)
{
	if(isAlive) {
		Vector2 delta = Vector2{(SCROLL_SPEED * timer->getElapsedMilliSeconds()), 0};
		topPipe->position = topPipe->position + delta;
		topPipeSprite->position = topPipeSprite->position + delta;
		bottomPipe->position = bottomPipe->position + delta;
		bottomPipeSprite->position = bottomPipeSprite->position + delta;
		if(topPipe->position.x <= -54) {
			isAlive = false;
		}
		Utilities::Rectangle topAABB(
			topPipe->position.x,
			topPipe->position.y,
			topPipe->width,
			topPipe->height + topPipeSprite->height
		);
	
		Utilities::Rectangle bottomAABB(
			bottomPipe->position.x,
			bottomPipe->position.y - bottomPipeSprite->height,
			bottomPipe->width,
			bottomPipe->height + bottomPipeSprite->height
		);

		topPipe->AABB = topAABB;
		bottomPipe->AABB = bottomAABB;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		bottomPipeDebugSprite->position = Point<float>{bottomAABB.position.x, bottomAABB.position.y};
		bottomPipeDebugSprite->width = bottomAABB.width;
		bottomPipeDebugSprite->height = bottomAABB.height;
		bottomPipeDebugSprite->offset = 22;

		topPipeDebugSprite->position = Point<float>{topAABB.position.x, topAABB.position.y};
		topPipeDebugSprite->width = topAABB.width;
		topPipeDebugSprite->height = topAABB.height;
		topPipeDebugSprite->offset = 22;
#endif
	}
}

void Pipes::draw(shared_ptr<ISpriteRenderer> renderer)
{
	if(isAlive) {
		renderer->drawSprite(topPipe, Point<float>{topPipe->position.x, topPipe->position.y});
		renderer->drawSprite(topPipeSprite, topPipeSprite->position);
		
		renderer->drawSprite(bottomPipe, Point<float>{bottomPipe->position.x, bottomPipe->position.y});
		renderer->drawSprite(bottomPipeSprite, bottomPipeSprite->position);

#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		renderer->drawSprite(bottomPipeDebugSprite);
		renderer->drawSprite(topPipeDebugSprite);
#endif
	}
}
