#include "StepTimer.h"
#include <cmath>
#include <exception>
#include <stdint.h>
#include <stdio.h>
#include <iostream>

using namespace std;
using namespace Utilities;


StepTimer::StepTimer() :
	m_elapsedMilliseconds(0),
	m_targetMilliseconds(1000 / 15),//CLOCKS_PER_SEC), //CLOCKS_PER_SEC / 60),
	m_elapsedSeconds(0),
	m_frameCount(0),
	m_framesPerSecond(0),
	m_framesThisSecond(0)
{
	// Initialisation
	gettimeofday(&m_lastFrameTime, NULL);
}

// Update timer state, calling the specified Update function the appropriate number of times.
void StepTimer::Tick(std::function<void()> update)
{
	timeval currentTime;
	gettimeofday(&currentTime, NULL);
	
	int delta = (currentTime.tv_usec - m_lastFrameTime.tv_usec) / 1000;
	if(delta < 0) delta = 0;
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
		}
		m_elapsedMilliseconds -= m_targetMilliseconds;
	}

	m_lastFrameTime = currentTime;
}