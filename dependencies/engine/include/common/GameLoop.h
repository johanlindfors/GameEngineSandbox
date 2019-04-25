#pragma once
#include "input/IInputManager.h"
#include "sprites/ISpriteRenderer.h"
#include "IGameLoopCallback.h"
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
		std::shared_ptr<IInputManager> GetInput() const { return mInputManager; }

	private:
		void Update();
		void Render();
		void Clear();

		std::shared_ptr<Utilities::IStepTimer> mTimer;
		SimpleRenderer *mSimpleRenderer;
		std::shared_ptr<ISpriteRenderer> mSpriteRenderer;
		std::shared_ptr<IInputManager> mInputManager;
		std::shared_ptr<IGameLoopCallback> mGameLoopCallback;
		bool mIsInitialized;
	};
} // namespace Engine
