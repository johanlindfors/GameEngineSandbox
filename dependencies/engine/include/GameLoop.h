# pragma once
#include "StepTimer.h"

namespace Engine {

	class GameLoop
	{
	public:

		GameLoop();

		void Tick();
		void OnWindowSizeChanged(int width, int height);
		void GetDefaultSize(int& width, int& height) const;

	private:
		void Update(Utilities::StepTimer const& timer);
		void Render();
		void Clear();

		Utilities::StepTimer m_timer;
	};
}
