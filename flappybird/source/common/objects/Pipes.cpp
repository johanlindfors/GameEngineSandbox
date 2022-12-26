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
	: TopPipe(make_shared<Pipe>(position))
	, BottomPipe(make_shared<Pipe>(position))
	, TopPipeSprite(make_shared<Sprite>())
	, BottomPipeSprite(make_shared<Sprite>())
#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
	, TopPipeDebugSprite(make_shared<Sprite>())
	, BottomPipeDebugSprite(make_shared<Sprite>())
#endif
	, IsAlive(true)
	, HasScored(false)
{
	Reset(position);

	TopPipe->Offset = 16;
	TopPipeSprite->Offset = 21;
	TopPipeSprite->Width = TopPipe->Width;
	
	BottomPipe->Offset = 17;
	BottomPipeSprite->Offset = 21;
	BottomPipeSprite->Width = TopPipe->Width;
}

void Pipes::Reset(Point<float> position)
{
	TopPipe->Position = Point<float>(position.X, position.Y);
	BottomPipe->Position = Point<float>(position.X, position.Y);

	TopPipe->Position.Y += 400;
	BottomPipe->Position.Y += 250;

	TopPipeSprite->Height = 505 - TopPipe->Position.Y - TopPipe->Height;
	TopPipeSprite->Position = Point<float>(TopPipe->Position.X, TopPipe->Position.Y + 25);

	BottomPipeSprite->Height = BottomPipe->Position.Y - 95;
	BottomPipeSprite->Position = Point<float>(BottomPipe->Position.X, BottomPipe->Position.Y - BottomPipeSprite->Height);

	IsAlive = true;
	HasScored = false;
}

void Pipes::Update(shared_ptr<IStepTimer> timer)
{
	if(IsAlive) {
		Vector2 delta = Vector2((SCROLL_SPEED * timer->GetElapsedMilliSeconds() / 1000.0f), 0);
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
		BottomPipeDebugSprite->Position = Point<float>(bottomAABB.Position.X, bottomAABB.Position.Y);
		BottomPipeDebugSprite->Width = bottomAABB.Width;
		BottomPipeDebugSprite->Height = bottomAABB.Height;
		BottomPipeDebugSprite->Offset = 22;

		TopPipeDebugSprite->Position = Point<float>(topAABB.Position.X, topAABB.Position.Y);
		TopPipeDebugSprite->Width = topAABB.Width;
		TopPipeDebugSprite->Height = topAABB.Height;
		TopPipeDebugSprite->Offset = 22;
#endif
	}
}

void Pipes::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	if(IsAlive) {
		renderer->DrawSprite(TopPipe, Point<float>(TopPipe->Position.X, TopPipe->Position.Y));
		renderer->DrawSprite(TopPipeSprite, TopPipeSprite->Position);
		
		renderer->DrawSprite(BottomPipe, Point<float>(BottomPipe->Position.X, BottomPipe->Position.Y));
		renderer->DrawSprite(BottomPipeSprite, BottomPipeSprite->Position);

#if defined(_DEBUG) && (DEBUG_TEXTURES_ENABLED == true)
		if(BottomSpriteCollided)
			renderer->DrawSprite(BottomPipeDebugSprite);
		if(TopSpriteCollided)
			renderer->DrawSprite(TopPipeDebugSprite);
#endif
	}
}
