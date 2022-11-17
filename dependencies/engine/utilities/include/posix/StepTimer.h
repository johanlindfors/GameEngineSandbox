#pragma once

#include <cmath>
#include <exception>
#include <stdint.h>
#include <functional>
#include "IStepTimer.h"
#include <sys/time.h> 


namespace Utilities
{
	// Helper class for animation and simulation timing.
	class StepTimer : public IStepTimer
	{
	public:
		StepTimer();

		// Get elapsed time since the previous Update call.
		double GetElapsedSeconds() const { return m_elapsedSeconds; }

		// Get total number of updates since start of the program.
		uint32_t GetFrameCount() const { return m_frameCount; }

		// Get the current framerate.
		uint32_t GetFramesPerSecond() const { return m_framesPerSecond; }

		// Set whether to use fixed or variable timestep mode.
		// void SetFixedTimeStep(bool isFixedTimestep) { m_isFixedTimeStep = isFixedTimestep; }

		// Set how often to call Update when in fixed timestep mode.
		// void SetTargetElapsedTicks(uint64_t targetElapsed) { m_targetElapsedTicks = targetElapsed; }
		void SetTargetElapsedSeconds(double targetElapsed) { m_targetMilliseconds = targetElapsed * 1000; }

		// // Integer format represents time using 10,000,000 ticks per second.
		// static const uint64_t TicksPerSecond = 10000000;

		// static double TicksToSeconds(uint64_t ticks) { return static_cast<double>(ticks) / TicksPerSecond; }
		// static uint64_t SecondsToMilliseconds(double seconds) { return 0; }//return static_cast<uint64_t>(seconds * CLOCKS_PER_SEC); }
	
		// Update timer state, calling the specified Update function the appropriate number of times.
		void Tick(std::function<void()> update);

	private:
		//clock_t m_lastFrameTime;
		timeval m_lastFrameTime;
		
		// Derived timing data uses a canonical tick format.
		unsigned int m_elapsedMilliseconds;
		unsigned int m_targetMilliseconds;
		unsigned int m_elapsedSeconds;

		// Members for tracking the framerate.
		uint32_t m_frameCount;
		uint32_t m_framesPerSecond;
		uint32_t m_framesThisSecond;
		// uint64_t m_qpcSecondCounter;

		// Members for configuring fixed timestep mode.
		// bool m_isFixedTimeStep;
		// uint64_t m_targetElapsedTicks;
	};
}
