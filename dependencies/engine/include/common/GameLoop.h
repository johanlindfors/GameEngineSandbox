#pragma once
#include "scenes/SceneManager.h"
#include "StepTimer.h"
#include <memory>

namespace Engine {

	class SimpleRenderer;

	class GameLoop {
	public:
		GameLoop();
		~GameLoop();

		void Initialize();
		void Tick();
		void UpdateWindowSize(int width, int height);
		void GetDefaultSize(int &width, int &height) const;

	private:
		void Update();
		void Render();
		void Clear();

		Utilities::StepTimer mTimer;
		SimpleRenderer *mSimpleRenderer;
		std::shared_ptr<SceneManager> mSceneManager;
		bool mIsInitialized;
	};
} // namespace Engine
