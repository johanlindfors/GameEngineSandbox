#include "Pipes.h"
#include "game/GameDefines.h"
#include "renderer/ISpriteRenderer.h"
#include "MathHelper.h"
#include "IStepTimer.h"

using namespace std;
using namespace Engine;
using namespace Utilities;

Pipes::Pipes(Vector2 position)
	: TopPipe(make_shared<Pipe>(position))
	, BottomPipe(make_shared<Pipe>(position))
	, TopPipeSprite(make_shared<Sprite>())
	, BottomPipeSprite(make_shared<Sprite>())
{
	TopPipe->Offset = 16;
	TopPipe->Position.m[1] += 145;
	TopPipeSprite->Offset = 21;
	TopPipeSprite->Width = TopPipe->Width;
	TopPipeSprite->Height = 505 - TopPipe->Y - 45;
	TopPipeSprite->Position = TopPipe->Position + Vector2(0,25);

	BottomPipe->Offset = 17;
	BottomPipeSprite->Offset = 21;
	BottomPipeSprite->Width = TopPipe->Width;
	BottomPipeSprite->Height = BottomPipe->Position.m[1] - 155;
	BottomPipeSprite->Position = BottomPipe->Position + Vector2(0,-BottomPipeSprite->Height);
}

void Pipes::Update(shared_ptr<IStepTimer> timer)
{
	Vector2 velocity(-200,0);
	Vector2 delta = Vector2(velocity.m[0] * (timer->GetElapsedMilliSeconds() / 1000.0f), 0);
	TopPipe->Position = TopPipe->Position + delta;
	TopPipeSprite->Position = TopPipeSprite->Position + delta;
	BottomPipe->Position = BottomPipe->Position + delta;
	BottomPipeSprite->Position = BottomPipeSprite->Position + delta;
}

void Pipes::Draw(shared_ptr<ISpriteRenderer> renderer)
{
	renderer->DrawSprite(TopPipe, TopPipe->Position);
	renderer->DrawSprite(TopPipeSprite, TopPipeSprite->Position);
	
	renderer->DrawSprite(BottomPipe, BottomPipe->Position);
	renderer->DrawSprite(BottomPipeSprite, BottomPipeSprite->Position);
}
