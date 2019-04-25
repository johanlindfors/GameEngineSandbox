#pragma once
#include <memory>

namespace Utilities {
	class IStepTimer;
}

namespace Engine {
	
	class GameScene {
	public:
		const char* ID;
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void UpdateScreenSize(int width, int height) = 0;
		virtual void Update(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
		virtual void Draw(std::shared_ptr<Utilities::IStepTimer> timer) = 0;
	};
}