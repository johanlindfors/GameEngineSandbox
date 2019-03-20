#include "GameLoop.h"
#include "SimpleRenderer.h"

using namespace std;
using namespace Engine;

GameLoop::GameLoop() 
{
	mSimpleRenderer = new SimpleRenderer();
}

GameLoop::~GameLoop()
{
	delete(mSimpleRenderer);
}

void GameLoop::Tick() 
{
	mTimer.Tick([&]()
	{
		Update(mTimer);
	});
	Render();
}

void GameLoop::OnWindowSizeChanged(int width, int height)
{
	// TODO: Handle window size changed events
	mSimpleRenderer->UpdateWindowSize(width, height);
}

void GameLoop::GetDefaultSize(int& width, int& height) const
{
	// TODO: Change to desired default window size (note minimum size is 320x200).
	width = 800;
	height = 600;
}

void GameLoop::Update(Utilities::StepTimer const& timer)
{
	float elapsedTime = float(timer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;
}

void GameLoop::Render()
{
	// Don't try to render anything before the first Update.
	if (mTimer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	mSimpleRenderer->Draw();
}

void GameLoop::Clear()
{
	// TODO: Add your clearing code here
}
