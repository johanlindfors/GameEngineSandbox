#include "Pipes.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "utilities/MathHelper.h"
#include "utilities/IStepTimer.h"
#include "game/GameDefines.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Pipes::Pipes(Point position)
	: TopPipe(make_shared<Pipe>(position))
	, BottomPipe(make_shared<Pipe>(position))
	, TopPipeSprite(make_shared<Sprite>())
	, BottomPipeSprite(make_shared<Sprite>())
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	, TopPipeDebugSprite(make_shared<Sprite>())
	, BottomPipeDebugSprite(make_shared<Sprite>())
#endif
	, IsAlive(true)
{
	Reset(position);

	TopPipe->Offset = 16;
	TopPipeSprite->Offset = 21;
	TopPipeSprite->Width = TopPipe->Width;
	
	BottomPipe->Offset = 17;
	BottomPipeSprite->Offset = 21;
	BottomPipeSprite->Width = TopPipe->Width;
}

void Pipes::Reset(Point position)
{
	TopPipe->Position = position;
	BottomPipe->Position = position;

	TopPipe->Position.Y += 400;
	BottomPipe->Position.Y += 250;

	TopPipeSprite->Height = 505 - TopPipe->Position.Y - TopPipe->Height;
	TopPipeSprite->Position = TopPipe->Position + Point(0,25);

	BottomPipeSprite->Height = BottomPipe->Position.Y - 155;
	BottomPipeSprite->Position = BottomPipe->Position + Point(0,-BottomPipeSprite->Height);

	IsAlive = true;
}

void Pipes::Update(shared_ptr<IStepTimer> timer)
{
	if(IsAlive) {
		Vector2 velocity(GROUND_SPEED, 0);
		Vector2 delta = Vector2(velocity.m[0] * (timer->GetElapsedMilliSeconds() / 1000.0f), 0);
		TopPipe->Position = TopPipe->Position + delta;
		TopPipeSprite->Position = TopPipeSprite->Position + delta;
		BottomPipe->Position = BottomPipe->Position + delta;
		BottomPipeSprite->Position = BottomPipeSprite->Position + delta;
		if(TopPipe->Position.X <= -54) {
			IsAlive = false;
		}
		Rectangle topAABB(
			TopPipe->Position.X,
			TopPipe->Position.Y,
			TopPipe->Width,
			TopPipe->Height + TopPipeSprite->Height
		);
	
		Rectangle bottomAABB(
			BottomPipe->Position.X,
			BottomPipe->Position.Y - BottomPipeSprite->Height,
			BottomPipe->Width,
			BottomPipe->Height + BottomPipeSprite->Height
		);

		TopPipe->AABB = topAABB;
		BottomPipe->AABB = bottomAABB;
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		BottomPipeDebugSprite->Position = Vector2(bottomAABB.X, bottomAABB.Y);
		BottomPipeDebugSprite->Width = bottomAABB.Width;
		BottomPipeDebugSprite->Height = bottomAABB.Height;
		BottomPipeDebugSprite->Offset = 22;

		TopPipeDebugSprite->Position = Vector2(topAABB.X, topAABB.Y);
		TopPipeDebugSprite->Width = topAABB.Width;
		TopPipeDebugSprite->Height = topAABB.Height;
		TopPipeDebugSprite->Offset = 22;
#endif
	}
}

void Pipes::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if(IsAlive) {
		renderer->DrawSprite(TopPipe, TopPipe->Position);
		renderer->DrawSprite(TopPipeSprite, TopPipeSprite->Position);
		
		renderer->DrawSprite(BottomPipe, BottomPipe->Position);
		renderer->DrawSprite(BottomPipeSprite, BottomPipeSprite->Position);

#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		if(BottomSpriteCollided)
			renderer->DrawSprite(BottomPipeDebugSprite);
		if(TopSpriteCollided)
			renderer->DrawSprite(TopPipeDebugSprite);
#endif
	}
}
