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
	class IResourceManager;
	class IFileSystem;

	class GameLoop {
	public:
		GameLoop();
		~GameLoop();

		void initialize(std::shared_ptr<Utilities::Config> config);
		void tick();
		void updateWindowSize(int width, int height);
		static void getDefaultSize(int &width, int &height);
		std::shared_ptr<IInputManager> getInput() const { return mInputManager; }

	private:
		void update() const;
		void render();
		void clear() const;

		std::shared_ptr<Utilities::IStepTimer> mTimer;
		std::shared_ptr<IRenderer> mRenderer;
		std::shared_ptr<IInputManager> mInputManager;
		std::shared_ptr<IGameLoopCallback> mGameLoopCallback;
		std::shared_ptr<ISceneManager> mSceneManager;
		std::shared_ptr<IResourceManager> mResourceManager;
		std::shared_ptr<IFileSystem> mFileSystem;
		bool mIsInitialized;
	};
} // namespace Engine