#pragma once
#include <memory>
#include "utilities/ScreenToGameCoordinatesConverter.hpp"

namespace Engine
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
	class FrameBufferRenderer;

	class GameLoop
	{
	public:
		GameLoop();
		~GameLoop();

		void initialize(std::shared_ptr<Engine::Config> config);
		void tick();
		void updateWindowSize(int width, int height);
		static void getDefaultSize(int &width, int &height);
		std::shared_ptr<IInputManager> getInput() const { return mInputManager; }
		Engine::ScreenToGameCoordinatesConverter ScreenToGameCoordinatesConverter;

	private:
		void handleInput() const;
		void update() const;
		void render();

		std::shared_ptr<Engine::IStepTimer> mTimer;
		std::shared_ptr<IRenderer> mRenderer;
		std::shared_ptr<IInputManager> mInputManager;
		std::shared_ptr<IGameLoopCallback> mGameLoopCallback;
		std::shared_ptr<ISceneManager> mSceneManager;
		std::shared_ptr<IResourceManager> mResourceManager;
		std::shared_ptr<IFileSystem> mFileSystem;
		std::shared_ptr<FrameBufferRenderer> mFrameBufferRenderer;
		bool mIsInitialized;
	};
} // namespace Engine
