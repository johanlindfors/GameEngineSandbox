#pragma once

#include <windows.h>
#include <stdint.h>
#include <functional>
#include "utilities/IStepTimer.h"
#include <chrono>

namespace Utilities
{
	class Timer 
	{
	public:
		Timer();

		void SetInterval(double milliseconds);
		void Update(std::function<void()> tick);

		void Pause();
		void Resume();
		void Reset();

	private:
		std::chrono::time_point<std::chrono::system_clock> mLastFrameTime;
		double mMillisecondsInterval;
		double mElapsedMilliseconds;
		bool mIsEnabled;
	};

	// Helper class for animation and simulation timing.
	class StepTimer : public IStepTimer
	{
	public:
		StepTimer() noexcept(false);
		void ResetElapsedTime();

		void Tick(std::function<void()>) override;

		// Get elapsed time since the previous Update call.
		// uint64_t GetElapsedTicks() const override { return m_elapsedTicks; }
		double GetElapsedSeconds() const override { return TicksToSeconds(m_elapsedTicks); }
		unsigned int GetElapsedMilliSeconds() const override { return TicksToSeconds(m_elapsedTicks) * 1000; }

		// Get total time since the start of the program.
		uint64_t GetTotalTicks() const { return m_totalTicks; }
		double GetTotalSeconds() const { return TicksToSeconds(m_totalTicks); }

		// Get total number of updates since start of the program.
		uint32_t GetFrameCount() const override { return m_frameCount; }

		// Get the current frame rate.
		uint32_t GetFramesPerSecond() const  { return m_framesPerSecond; }

		// Set whether to use fixed or variable time step mode.
		void SetFixedTimeStep(bool isFixedTimeStep)  { m_isFixedTimeStep = isFixedTimeStep; }

		// Set how often to call Update when in fixed time step mode.
		void SetTargetElapsedTicks(uint64_t targetElapsed)  { m_targetElapsedTicks = targetElapsed; }
		void SetTargetElapsedSeconds(double targetElapsed) override { m_targetElapsedTicks = SecondsToTicks(targetElapsed); }

		// Integer format represents time using 10,000,000 ticks per second.
		static const uint64_t TicksPerSecond = 10000000;

		static double TicksToSeconds(uint64_t ticks) { return static_cast<double>(ticks) / TicksPerSecond; }
		static uint64_t SecondsToTicks(double seconds) { return static_cast<uint64_t>(seconds * TicksPerSecond); }

		// After an intentional timing discontinuity (for instance a blocking IO operation)
		// call this to avoid having the fixed timestep logic attempt a set of catch-up 
		// Update calls.

	private:
		// Source timing data uses QPC units.
		LARGE_INTEGER m_qpcFrequency;
		LARGE_INTEGER m_qpcLastTime;
		uint64_t m_qpcMaxDelta;

		// Derived timing data uses a canonical tick format.
		uint64_t m_elapsedTicks;
		uint64_t m_totalTicks;
		uint64_t m_leftOverTicks;

		// Members for tracking the framerate.
		uint32_t m_frameCount;
		uint32_t m_framesPerSecond;
		uint32_t m_framesThisSecond;
		uint64_t m_qpcSecondCounter;

		// Members for configuring fixed timestep mode.
		bool m_isFixedTimeStep;
		uint64_t m_targetElapsedTicks;
	};
}
