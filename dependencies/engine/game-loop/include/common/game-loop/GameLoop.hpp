#pragma once
#include <memory>
#include "utilities/ScreenToGameCoordinatesConverter.hpp"

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
	class ResourceManager;
	class IFileSystem;
	class IAudioManager;
	class FrameBufferRenderer;

	class GameLoop
	{
	public:
		GameLoop();
		~GameLoop();

		void initialize(std::shared_ptr<Utilities::Config> config);
		void tick();
		void updateWindowSize(int width, int height);
		static void getDefaultSize(int &width, int &height);
		std::shared_ptr<IInputManager> getInput() const { return mInputManager; }
		Utilities::ScreenToGameCoordinatesConverter ScreenToGameCoordinatesConverter;

	private:
		void handleInput() const;
		void update() const;
		void render();

		std::shared_ptr<Utilities::IStepTimer> mTimer;
		std::shared_ptr<IRenderer> mRenderer;
		std::shared_ptr<IInputManager> mInputManager;
		std::shared_ptr<IGameLoopCallback> mGameLoopCallback;
		std::shared_ptr<ISceneManager> mSceneManager;
		std::shared_ptr<ResourceManager> mResourceManager;
		std::shared_ptr<IFileSystem> mFileSystem;
		std::shared_ptr<IAudioManager> mAudioManager;
		std::shared_ptr<FrameBufferRenderer> mFrameBufferRenderer;
		bool mIsInitialized;
	};
} // namespace Engine
