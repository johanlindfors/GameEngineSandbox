#pragma once
#include <memory>
#include "StepTimer.h"

namespace Engine {
	
	class GameScene {
	public:
		const char* ID;
		virtual void Load() = 0;
		virtual void Unload() = 0;
		virtual void UpdateScreenSize(int width, int height) = 0;
		virtual void Update(Utilities::StepTimer const& timer) = 0;
		virtual void Draw(Utilities::StepTimer const& timer) = 0;
	};
}