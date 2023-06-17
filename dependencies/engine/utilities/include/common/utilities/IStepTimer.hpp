#pragma once
#include <functional>

namespace Utilities
{
	class IStepTimer
	{
	public:
		virtual ~IStepTimer() = default;

		virtual void tick(std::function<void()>,std::function<void()>,std::function<void()>) = 0;

		virtual unsigned int getDeltaMicroSeconds() const = 0;
		//  Get elapsed time since the previous Update call.
		virtual double getElapsedSeconds() const = 0;
		virtual double getElapsedMilliSeconds() const = 0;
		virtual unsigned int getElapsedMicroSeconds() const = 0;

		// Get total number of updates since start of the program.
		virtual uint32_t getFrameCount() const  = 0;

		// Get the current framerate.
		virtual uint32_t getFramesPerSecond() const = 0;

		// Set whether to use fixed or variable timestep mode.
		virtual void setFixedTimeStep(bool isFixedTimestep) = 0;

		// Set how often to call Update when in fixed timestep mode.
		virtual void setTargetElapsedSeconds(double targetElapsed) = 0;

		// Integer format represents time using 10,000,000 ticks per second.
		static const uint64_t ticksPerSecond = 10000000;
	};
}
