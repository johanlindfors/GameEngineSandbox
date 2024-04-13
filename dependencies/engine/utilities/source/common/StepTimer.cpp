#include "utilities/StepTimer.hpp"
#include <cmath>
#include <exception>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;
using namespace Utilities;

Timer::Timer()
	: mIsEnabled(true), mElapsedMicroSeconds(0), mLastFrameTime(std::chrono::system_clock::now()), mMicroSecondsInterval(0)
{
}

void Timer::setInterval(double microseconds)
{
	mMicroSecondsInterval = microseconds;
}

void Timer::update(function<void()> tick)
{
	auto currentTime = system_clock::now();

	if (mIsEnabled)
	{
		auto delta = duration_cast<microseconds>(currentTime - mLastFrameTime).count();
		if (delta < 0)
			delta = 0;
		mElapsedMicroSeconds += delta;
		if (mElapsedMicroSeconds >= mMicroSecondsInterval)
		{
			tick();

			mElapsedMicroSeconds -= mMicroSecondsInterval;
		}
	}
	mLastFrameTime = currentTime;
}

void Timer::pause()
{
	mIsEnabled = false;
}

void Timer::resume()
{
	mIsEnabled = true;
}

void Timer::reset()
{
	mLastFrameTime = system_clock::now();
	mElapsedMicroSeconds = 0;
	resume();
}

StepTimer::StepTimer()
	: m_elapsedMicroSeconds(0), m_targetMicroSeconds(1000000.0 / 15.0), m_elapsedSeconds(0.0), m_frameCount(0), m_framesPerSecond(0), m_framesThisSecond(0), m_isFixedTimeStep(false)

{
	// Initialisation
	m_lastFrameTime = system_clock::now();
}

// Update timer state, calling the specified Update function the appropriate number of times.
void StepTimer::tick(
	function<void()> processInput,
	function<void()> update,
	function<void()> render)
{
	auto currentTime = system_clock::now();
	auto delta = duration_cast<microseconds>(currentTime - m_lastFrameTime).count();
	m_lastFrameTime = currentTime;

	if (delta <= 0)
		delta = 1;

	m_delta = delta;
	m_elapsedMicroSeconds += static_cast<unsigned int>(delta);
	m_elapsedSeconds += static_cast<double>(delta / 1000000.0);
	m_frameCount++;
	m_framesThisSecond++;

	if (m_elapsedMicroSeconds >= 1000000)
	{
		m_elapsedMicroSeconds -= 1000000;
		m_framesPerSecond = m_framesThisSecond;
		m_framesThisSecond = 0;
		printf("FPS %d\n", m_framesPerSecond);
	}

	if (m_isFixedTimeStep)
	{
		while (m_elapsedMicroSeconds >= m_targetMicroSeconds)
		{
			update();
			m_elapsedMicroSeconds -= m_targetMicroSeconds;
		}
		render();
		processInput();
		auto sleepForMicroSeconds = duration_cast<microseconds>(currentTime - system_clock::now()).count() + m_targetMicroSeconds;
		if (sleepForMicroSeconds > 0)
			this_thread::sleep_for(microseconds(sleepForMicroSeconds));
	}
	else
	{
		update();
		render();
		processInput();
	}
}
