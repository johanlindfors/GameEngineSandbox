#include "GameLoop.h"

using namespace Engine;

GameLoop::GameLoop() 
{

}

void GameLoop::Tick() 
{
	m_timer.Tick([&]()
	{
		Update(m_timer);
	});

	Render();
}

void GameLoop::OnWindowSizeChanged(int width, int height)
{
	// TODO: Handle window size changed events
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
	if (m_timer.GetFrameCount() == 0)
	{
		return;
	}

	Clear();

	// TODO: Add your rendering code here
}

void GameLoop::Clear()
{
	// TODO: Add your clearing code here
}
