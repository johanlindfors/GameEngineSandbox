#include "StepTimer.h"
#include <cmath>
#include <exception>
#include <stdint.h>
#include <stdio.h>
#include <iostream>

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

StepTimer::StepTimer() 
	: m_elapsedMilliseconds(0)
	, m_targetMilliseconds(1000 / 15) //CLOCKS_PER_SEC), //CLOCKS_PER_SEC / 60),
	, m_elapsedSeconds(0)
	, m_frameCount(0)
	, m_framesPerSecond(0)
	, m_framesThisSecond(0)
	, m_isFixedTimeStep(false)
	
{
	// Initialisation
	m_lastFrameTime = std::chrono::system_clock::now();
}

// Update timer state, calling the specified Update function the appropriate number of times.
void StepTimer::Tick(std::function<void()> update)
{
	auto currentTime =  std::chrono::system_clock::now();
	
	auto delta = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - m_lastFrameTime).count();
	if(delta < 0) delta = 0;
	if(m_isFixedTimeStep) {
		m_elapsedMilliseconds += delta;
		m_elapsedSeconds += delta;
		if(m_elapsedMilliseconds >= m_targetMilliseconds) {
			m_frameCount++;
			m_framesThisSecond++;
			update();

			if(m_elapsedSeconds >= 1000) {
				m_elapsedSeconds -= 1000;
				m_framesPerSecond = m_framesThisSecond;
				m_framesThisSecond = 0;
				printf("FPS %d\n", m_framesPerSecond);
			}
			m_elapsedMilliseconds = 0;//= m_targetMilliseconds;
		}
	} else {
		m_elapsedMilliseconds = delta;
		m_elapsedSeconds += delta;
		update();
		m_frameCount++;
		m_framesThisSecond++;
		if(m_elapsedSeconds >= 1000) {
			m_elapsedSeconds -= 1000;
			m_framesPerSecond = m_framesThisSecond;
			m_framesThisSecond = 0;
			printf("FPS %d\n", m_framesPerSecond);
		}
	}

	m_lastFrameTime = currentTime;
}