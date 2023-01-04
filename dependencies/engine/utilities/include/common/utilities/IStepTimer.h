#pragma once
#include <functional>

namespace Utilities
{
	// Helper class for animation and simulation timing.
	class IStepTimer
	{
	public:
		virtual ~IStepTimer() = default;
		// virtual void ResetElapsedTime() = 0;

		virtual void Tick(std::function<void()>,std::function<void()>,std::function<void()>) = 0;

		// // Get elapsed time since the previous Update call.
		// virtual uint64_t GetElapsedTicks() const = 0;
		virtual double GetElapsedSeconds() const = 0;
		virtual unsigned int GetElapsedMilliSeconds() const = 0;
		// // Get total time since the start of the program.
		// virtual uint64_t GetTotalTicks() const = 0;
		// virtual double GetTotalSeconds() const  = 0;

		// Get total number of updates since start of the program.
		virtual uint32_t GetFrameCount() const  = 0;

		// // Get the current framerate.
		// virtual uint32_t GetFramesPerSecond() const = 0;

		// Set whether to use fixed or variable timestep mode.
		virtual void SetFixedTimeStep(bool isFixedTimestep) = 0;

		// // Set how often to call Update when in fixed timestep mode.
		// virtual void SetTargetElapsedTicks(uint64_t targetElapsed) = 0;
		virtual void SetTargetElapsedSeconds(double targetElapsed) = 0;

		// Integer format represents time using 10,000,000 ticks per second.
		static const uint64_t TicksPerSecond = 10000000;

		// static double TicksToSeconds(uint64_t ticks) { return static_cast<double>(ticks) / TicksPerSecond; }
		// static uint64_t SecondsToTicks(double seconds) { return static_cast<uint64_t>(seconds * TicksPerSecond); }
	};
}
