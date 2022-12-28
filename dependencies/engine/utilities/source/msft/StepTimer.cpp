#include "StepTimer.h"
#include <cmath>
#include <exception>
#include <stdint.h>
#include <Windows.h>

using namespace std;
using namespace Utilities;


Timer::Timer() 
	: mIsEnabled(true)
	, mElapsedMilliseconds(0)
	, mLastFrameTime(std::chrono::system_clock::now())
{ }

void Timer::SetInterval(double milliseconds)
{
	mMillisecondsInterval = milliseconds;
}

void Timer::Update(std::function<void()> tick)
{
	auto currentTime =  std::chrono::system_clock::now();
	
	if(mIsEnabled) {
		auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - mLastFrameTime).count();
		if(delta < 0) delta = 0;
		mElapsedMilliseconds += delta;
		if(mElapsedMilliseconds >= mMillisecondsInterval) {
 			tick();

			mElapsedMilliseconds -= mMillisecondsInterval;
		}
	}
	mLastFrameTime = currentTime;
}

void Timer::Pause()
{
	mIsEnabled = false;
}

void Timer::Resume()
{
	mIsEnabled = true;
}

void Timer::Reset()
{
	mLastFrameTime = std::chrono::system_clock::now();
	mElapsedMilliseconds = 0;
	Resume();
}

StepTimer::StepTimer() noexcept(false) :
	m_elapsedTicks(0),
	m_totalTicks(0),
	m_leftOverTicks(0),
	m_frameCount(0),
	m_framesPerSecond(0),
	m_framesThisSecond(0),
	m_qpcSecondCounter(0),
	m_isFixedTimeStep(false),
	m_targetElapsedTicks(TicksPerSecond / 60)
{
	if (!QueryPerformanceFrequency(&m_qpcFrequency))
	{
		throw std::exception("QueryPerformanceFrequency");
	}

	if (!QueryPerformanceCounter(&m_qpcLastTime))
	{
		throw std::exception("QueryPerformanceCounter");
	}

	// Initialize max delta to 1/10 of a second.
	m_qpcMaxDelta = static_cast<uint64_t>(m_qpcFrequency.QuadPart / 10);
}

void StepTimer::ResetElapsedTime()
{
	if (!QueryPerformanceCounter(&m_qpcLastTime))
	{
		throw std::exception("QueryPerformanceCounter");
	}

	m_leftOverTicks = 0;
	m_framesPerSecond = 0;
	m_framesThisSecond = 0;
	m_qpcSecondCounter = 0;
}

// Update timer state, calling the specified Update function the appropriate number of times.
void StepTimer::Tick(std::function<void()> update)
{
	// Query the current time.
	LARGE_INTEGER currentTime;

	if (!QueryPerformanceCounter(&currentTime))
	{
		throw std::exception("QueryPerformanceCounter");
	}

	uint64_t timeDelta = currentTime.QuadPart - m_qpcLastTime.QuadPart;

	m_qpcLastTime = currentTime;
	m_qpcSecondCounter += timeDelta;

	// Clamp excessively large time deltas (e.g. after paused in the debugger).
	if (timeDelta > m_qpcMaxDelta)
	{
		timeDelta = m_qpcMaxDelta;
	}

	// Convert QPC units into a canonical tick format. This cannot overflow due to the previous clamp.
	timeDelta *= TicksPerSecond;
	timeDelta /= m_qpcFrequency.QuadPart;

	const auto lastFrameCount = m_frameCount;

	if (m_isFixedTimeStep)
	{
		// Fixed timestep update logic

		// If the app is running very close to the target elapsed time (within 1/4 of a millisecond) just clamp
		// the clock to exactly match the target value. This prevents tiny and irrelevant errors
		// from accumulating over time. Without this clamping, a game that requested a 60 fps
		// fixed update, running with vsync enabled on a 59.94 NTSC display, would eventually
		// accumulate enough tiny errors that it would drop a frame. It is better to just round 
		// small deviations down to zero to leave things running smoothly.

		if (static_cast<uint64_t>(std::abs(static_cast<int64_t>(timeDelta - m_targetElapsedTicks))) < TicksPerSecond / 4000)
		{
			timeDelta = m_targetElapsedTicks;
		}

		m_leftOverTicks += timeDelta;

		while (m_leftOverTicks >= m_targetElapsedTicks)
		{
			m_elapsedTicks = m_targetElapsedTicks;
			m_totalTicks += m_targetElapsedTicks;
			m_leftOverTicks -= m_targetElapsedTicks;
			m_frameCount++;

			update();
		}
	}
	else
	{
		// Variable timestep update logic.
		m_elapsedTicks = timeDelta;
		m_totalTicks += timeDelta;
		m_leftOverTicks = 0;
		m_frameCount++;

		update();
	}

	// Track the current framerate.
	if (m_frameCount != lastFrameCount)
	{
		m_framesThisSecond++;
	}

	if (m_qpcSecondCounter >= static_cast<uint64_t>(m_qpcFrequency.QuadPart))
	{
		m_framesPerSecond = m_framesThisSecond;
		m_framesThisSecond = 0;
		m_qpcSecondCounter %= m_qpcFrequency.QuadPart;
	}
}