#include "GameLoop.h"
#include "SimpleRenderer.h"

using namespace std;
using namespace Engine;

GameLoop::GameLoop() 
{
	mSimpleRenderer = new SimpleRenderer();
	mSceneManager = make_unique<SceneManager>();
	mTimer.SetFixedTimeStep(true);
}

GameLoop::~GameLoop()
{
	delete(mSimpleRenderer);
	mSceneManager.reset(nullptr);
}

void GameLoop::Tick() 
{
	mTimer.Tick([&]()
	{
		Update();
	});
	Render();
}

void GameLoop::UpdateWindowSize(int width, int height)
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

void GameLoop::Update()
{
	float elapsedTime = float(mTimer.GetElapsedSeconds());

	// TODO: Add your game logic here.
	elapsedTime;
	mSimpleRenderer->Update(mTimer);
	mSceneManager->Update(mTimer);
}

void GameLoop::Render()
{
	// Don't try to render anything before the first Update.
	if (mTimer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	mSimpleRenderer->Draw(mTimer);
	mSceneManager->Draw(mTimer);
}

void GameLoop::Clear()
{
	// TODO: Add your clearing code here
}
