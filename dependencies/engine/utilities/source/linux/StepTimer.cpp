#include "StepTimer.h"
#include <cmath>
#include <exception>
#include <stdint.h>
#include <stdio.h>

using namespace Utilities;

// Update timer state, calling the specified Update function the appropriate number of times.
void StepTimer::Tick(std::function<void()> update)
{
	clock_t currentTime = clock();

	auto delta = (currentTime - m_lastFrameTime);
	m_elapsedMilliseconds += delta;
    //printf("Elapsed milliseconds: %d delta: %i\n", m_elapsedMilliseconds, delta);
	if(m_elapsedMilliseconds >= m_targetMilliseconds) {
		m_lastFrameTime = currentTime;
		m_elapsedMilliseconds -= m_targetMilliseconds;
		//printf("Elapsed milliseconds: %d delta: %i\n", m_elapsedMilliseconds, delta);
		m_frameCount++;
		update();
	}
}