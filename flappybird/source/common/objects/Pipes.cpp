#include "Pipes.h"
#include "game/GameDefines.h"
#include "renderers/SpriteRenderer.h"
#include "utilities/MathHelper.h"
#include "utilities/IStepTimer.h"
#include "game/GameDefines.h"
#include "utilities/IOC.hpp"
#include "resources/IResourceManager.h"

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

	auto resourceManager = IOCContainer::instance().resolve<IResourceManager>();
	auto texture = resourceManager->getTexture("atlas.png");
	topPipe->texture = texture;
	topPipeSprite->texture = texture;
	bottomPipe->texture = texture;
	bottomPipeSprite->texture = texture;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	topPipeDebugSprite->texture = texture;
	bottomPipeDebugSprite->texture = texture;
#endif

	topPipeSprite->size.width = topPipe->size.width;
	topPipe->offset = {
		402.0f / 512.0f, (512.0f - 430.0f) / 512.0f,
		52.0f / 512.0f, 25.0f / 512.0f
	}; // 402, 405, 454, 430
	topPipeSprite->offset = {
		402.0f / 512.0f, (512.0f - 120.0f) / 512.0f,
		52.0f / 512.0f, 10.0f / 512.0f
	}; // 402, 110, 454, 120
	
	bottomPipeSprite->size.width = topPipe->size.width;
	bottomPipe->offset = {
		458.0f / 512.0f, (512.0f - 135.0f) / 512.0f,
		52.0f / 512.0f, 25.0f / 512.0f
	}; // 458, 110, 510, 135
	bottomPipeSprite->offset = {
		402.0f / 512.0f, (512.0f - 120.0f) / 512.0f,
		52.0f / 512.0f, 10.0f / 512.0f
	}; // 402, 110, 454, 120
}

void Pipes::reset(Point<float> position)
{
	topPipe->position = Point<float>{position.x, position.y};
	bottomPipe->position = Point<float>{position.x, position.y};

	topPipe->position.y += 400;
	bottomPipe->position.y += 250;

	topPipeSprite->size.height = 505.0f - topPipe->position.y - topPipe->size.height;
	topPipeSprite->position = Point<float>{topPipe->position.x, topPipe->position.y + 25};

	bottomPipeSprite->size.height = bottomPipe->position.y - 95.0f;
	bottomPipeSprite->position = Point<float>{bottomPipe->position.x, bottomPipe->position.y - bottomPipeSprite->size.height};

	isAlive = true;
	hasScored = false;
}

void Pipes::update(shared_ptr<IStepTimer> timer)
{
	if(isAlive) {
		Vector2 delta = Vector2{(SCROLL_SPEED * static_cast<float>(timer->getElapsedMilliSeconds())), 0};
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
			topPipe->size.width,
			topPipe->size.height + topPipeSprite->size.height
		);
	
		Utilities::Rectangle bottomAABB(
			bottomPipe->position.x,
			bottomPipe->position.y - bottomPipeSprite->size.height,
			bottomPipe->size.width,
			bottomPipe->size.height + bottomPipeSprite->size.height
		);

		topPipe->AABB = topAABB;
		bottomPipe->AABB = bottomAABB;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		bottomPipeDebugSprite->position = Point<float>{bottomAABB.position.x, bottomAABB.position.y};
		bottomPipeDebugSprite->size = bottomAABB.size;
		bottomPipeDebugSprite->offset = {
			1.0f / 512.0f, (512.0f - 371.0f) / 512.0f,
			1.0f / 512.0f, 1.0f / 512.0f
		}; // 1, 364, 8, 371

		topPipeDebugSprite->position = Point<float>{topAABB.position.x, topAABB.position.y};
		topPipeDebugSprite->size = topAABB.size;
		topPipeDebugSprite->offset = {
			1.0f / 512.0f, (512.0f - 371.0f) / 512.0f,
			1.0f / 512.0f, 1.0f / 512.0f
		}; // 1, 364, 8, 371
#endif
	}
}

void Pipes::draw(shared_ptr<IRenderer> renderer)
{
	auto spriteRenderer = static_pointer_cast<SpriteRenderer>(renderer);
	if(spriteRenderer && isAlive) {
		spriteRenderer->drawSprite(topPipe, Point<float>{topPipe->position.x, topPipe->position.y});
		spriteRenderer->drawSprite(topPipeSprite, topPipeSprite->position);
		
		spriteRenderer->drawSprite(bottomPipe, Point<float>{bottomPipe->position.x, bottomPipe->position.y});
		spriteRenderer->drawSprite(bottomPipeSprite, bottomPipeSprite->position);

#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		spriteRenderer->drawSprite(bottomPipeDebugSprite);
		spriteRenderer->drawSprite(topPipeDebugSprite);
#endif
	}
}
