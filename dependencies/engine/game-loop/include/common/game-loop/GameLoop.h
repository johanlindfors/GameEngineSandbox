#pragma once
#include <memory>

namespace Utilities
{
	class IStepTimer;
	struct Config;
}

namespace Engine 
{

	class IRenderer;
	class IInputManager;
	class ISceneManager;
	class IGameLoopCallback;

	class GameLoop {
	public:
		GameLoop();
		~GameLoop();

		void Initialize(std::shared_ptr<Utilities::Config> config);
		void Tick();
		void UpdateWindowSize(int width, int height);
		static void GetDefaultSize(int &width, int &height);
		std::shared_ptr<IInputManager> GetInput() const { return mInputManager; }

	private:
		void Update() const;
		void Render();
		void Clear() const;

		std::shared_ptr<Utilities::IStepTimer> mTimer;
		std::shared_ptr<IRenderer> mRenderer;
		std::shared_ptr<IInputManager> mInputManager;
		std::shared_ptr<IGameLoopCallback> mGameLoopCallback;
		std::shared_ptr<ISceneManager> mSceneManager;
		bool mIsInitialized;
	};
} // namespace Engine
