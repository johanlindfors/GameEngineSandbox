# pragma once
#include "StepTimer.h"
#include <memory>

namespace Engine {

	class SimpleRenderer;

	class GameLoop
	{
	public:

		GameLoop();
		~GameLoop();

		void Tick();
		void OnWindowSizeChanged(int width, int height);
		void GetDefaultSize(int& width, int& height) const;

	private:
		void Update(Utilities::StepTimer const& timer);
		void Render();
		void Clear();

		Utilities::StepTimer mTimer;
		SimpleRenderer* mSimpleRenderer;
	};
}
