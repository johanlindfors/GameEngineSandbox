#include "StepTimer.h"
#include <cmath>
#include <exception>
#include <stdint.h>
#include <stdio.h>
#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace Utilities;

Timer::Timer() 
	: mIsEnabled(true)
	, mElapsedMilliseconds(0)
	, mLastFrameTime(std::chrono::system_clock::now())
	, mMillisecondsInterval(0)
{ }

void Timer::setInterval(double milliseconds)
{
	mMillisecondsInterval = milliseconds;
}

void Timer::update(std::function<void()> tick)
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
	mLastFrameTime = std::chrono::system_clock::now();
	mElapsedMilliseconds = 0;
	resume();
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
void StepTimer::tick(std::function<void()> processInput,std::function<void()> update, std::function<void()> render)
{
	auto currentTime =  std::chrono::system_clock::now();
	auto delta = std::chrono::duration_cast<std::chrono::microseconds>(currentTime - m_lastFrameTime).count();
	m_lastFrameTime = currentTime;

	if(delta <= 0) delta = 1;

	// if(m_isFixedTimeStep) {
	// 	m_elapsedMilliseconds += static_cast<unsigned int>(delta);
	// 	m_elapsedSeconds += static_cast<unsigned int>(delta);
	// 	while(m_elapsedMilliseconds >= m_targetMilliseconds) {
	// 		update();
	// 		m_elapsedMilliseconds -= m_targetMilliseconds;
	// 	}
	// 	m_frameCount++;
	// 	m_framesThisSecond++;
	// 	render();

	// 	if(m_elapsedSeconds >= 1000) {
	// 		m_elapsedSeconds -= 1000;
	// 		m_framesPerSecond = m_framesThisSecond;
	// 		m_framesThisSecond = 0;
	// 		printf("FPS %d\n", m_framesPerSecond);
	// 	}
	// 	auto sleepForMilliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - std::chrono::system_clock::now()).count() + m_targetMilliseconds;
	// 	if(sleepForMilliseconds > 0)
	// 		std::this_thread::sleep_for(std::chrono::milliseconds(sleepForMilliseconds));
	// } else {
		m_elapsedMilliseconds += static_cast<unsigned int>(delta);;
		m_elapsedSeconds += static_cast<unsigned int>(delta);;
		update();
		render();
		m_frameCount++;
		m_framesThisSecond++;
		if(m_elapsedMilliseconds >= 1000 000) {
			m_elapsedMilliseconds -= 1000 000;
			m_framesPerSecond = m_framesThisSecond;
			m_framesThisSecond = 0;
			printf("FPS %d\n", m_framesPerSecond);
		}
	// }
}