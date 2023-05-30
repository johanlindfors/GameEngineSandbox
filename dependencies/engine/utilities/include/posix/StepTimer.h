#pragma once

#include <cmath>
#include <exception>
#include <stdint.h>
#include <functional>
#include "utilities/IStepTimer.h"
#include <sys/time.h> 
#include <chrono>

namespace Utilities
{
	class Timer 
	{
	public:
		Timer();

		void setInterval(double microseconds);
		void update(std::function<void()> tick);

		void pause();
		void resume();
		void reset();

	private:
		std::chrono::time_point<std::chrono::system_clock> mLastFrameTime;
		double mMicroSecondsInterval;
		double mElapsedMicroSeconds;
		bool mIsEnabled;
	};

	// Helper class for animation and simulation timing.
	class StepTimer : public IStepTimer
	{
	public:
		StepTimer();

		// Get elapsed time since the previous Update call.
		double getElapsedSeconds() const { 
			return m_elapsedMicroSeconds / 1000000.0;
		}
		
		double getElapsedMilliSeconds() const { 
			if(m_elapsedMicroSeconds > m_targetMicroSeconds)
				return m_targetMicroSeconds / 1000.0;
			return m_elapsedMicroSeconds / 1000.0;
		}

		unsigned int getElapsedMicroSeconds() const { 
			if(m_elapsedMicroSeconds > m_targetMicroSeconds)
				return m_targetMicroSeconds;
			return m_elapsedMicroSeconds;
		}

		// Get total number of updates since start of the program.
		uint32_t getFrameCount() const { return m_frameCount; }

		// Get the current framerate.
		uint32_t getFramesPerSecond() const { return m_framesPerSecond; }

		// Set whether to use fixed or variable timestep mode.
		void setFixedTimeStep(bool isFixedTimestep) { m_isFixedTimeStep = isFixedTimestep; }

		// Set how often to call Update when in fixed timestep mode.
		void setTargetElapsedSeconds(double targetElapsed) { m_targetMicroSeconds = targetElapsed * 1000000; }
	
		// Update timer state, calling the specified functions the appropriate number of times.
		void tick(std::function<void()> update,std::function<void()>,std::function<void()>);

	private:
		 std::chrono::time_point<std::chrono::system_clock> m_lastFrameTime;
		
		unsigned int m_elapsedSeconds;
		unsigned int m_elapsedMicroSeconds;
		unsigned int m_targetMicroSeconds;
		bool m_isFixedTimeStep;

		// Members for tracking the framerate.
		uint32_t m_frameCount;
		uint32_t m_framesPerSecond;
		uint32_t m_framesThisSecond;
	};
}
