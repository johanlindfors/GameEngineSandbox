#include "Pipes.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "MathHelper.h"
#include "IStepTimer.h"
#include "game/GameDefines.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Pipes::Pipes(Vector2 position)
	: TopPipe(make_shared<Pipe>(position))
	, BottomPipe(make_shared<Pipe>(position))
	, TopPipeSprite(make_shared<Sprite>())
	, BottomPipeSprite(make_shared<Sprite>())
#ifdef _DEBUG
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

void Pipes::Reset(Vector2 position)
{
	TopPipe->Position = position;
	BottomPipe->Position = position;

	TopPipe->Position.m[1] += 400;
	BottomPipe->Position.m[1] += 250;

	TopPipeSprite->Height = 505 - TopPipe->Position.m[1] - TopPipe->Height;
	TopPipeSprite->Position = TopPipe->Position + Vector2(0,25);

	BottomPipeSprite->Height = BottomPipe->Position.m[1] - 155;
	BottomPipeSprite->Position = BottomPipe->Position + Vector2(0,-BottomPipeSprite->Height);

	IsAlive = true;
}

bool Pipes::Intersects(Circle circle, Rectangle rect)
{
	Vector2 circleDistance(0,0);
    circleDistance.m[0] = abs(circle.X - rect.X);
    circleDistance.m[1] = abs(circle.Y - rect.Y);

    if (circleDistance.m[0] > (rect.Width/2 + circle.Radius)) { return false; }
    if (circleDistance.m[1] > (rect.Height/2 + circle.Radius)) { return false; }

    if (circleDistance.m[0] <= (rect.Width/2)) { return true; } 
    if (circleDistance.m[1] <= (rect.Height/2)) { return true; }

    auto cornerDistance_sq = pow(circleDistance.m[0] - rect.Width/2, 2) +
                         	 pow(circleDistance.m[1] - rect.Height/2, 2);

    return (cornerDistance_sq <= (circle.Radius)^2);
}

bool Pipes::Intersects(Rectangle r1, Rectangle r2)
{
	return r1.X <= (r2.X + r2.Width) && (r1.X + r1.Width) >= r2.X &&
           r1.Y <= (r2.Y + r2.Height) && (r1.Y + r1.Height) >= r2.Y;
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
		if(TopPipe->Position.m[0] <= -54) {
			IsAlive = false;
		}
		Rectangle topAABB(
			TopPipe->Position.m[0],
			TopPipe->Position.m[1],
			TopPipe->Width,
			TopPipe->Height + TopPipeSprite->Height
		);
	
		Rectangle bottomAABB(
			BottomPipe->Position.m[0],
			BottomPipe->Position.m[1] - BottomPipeSprite->Height,
			BottomPipe->Width,
			BottomPipe->Height + BottomPipeSprite->Height
		);

		TopPipe->AABB = topAABB;
		BottomPipe->AABB = bottomAABB;
#ifdef _DEBUG
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

#ifdef _DEBUG
		if(BottomSpriteCollided)
			renderer->DrawSprite(BottomPipeDebugSprite);
		if(TopSpriteCollided)
			renderer->DrawSprite(TopPipeDebugSprite);
#endif
	}
}
