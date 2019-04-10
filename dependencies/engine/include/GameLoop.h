# pragma once
#include "StepTimer.h"
#include <memory>
#include "SceneManager.h"

namespace Engine {

	class SimpleRenderer;

	class GameLoop
	{
	public:

		GameLoop();
		~GameLoop();

		void Tick();
		void UpdateWindowSize(int width, int height);
		void GetDefaultSize(int& width, int& height) const;

	private:
		void Update();
		void Render();
		void Clear();

		Utilities::StepTimer mTimer;
		SimpleRenderer* mSimpleRenderer;
		std::unique_ptr<SceneManager> mSceneManager;
	};
}
