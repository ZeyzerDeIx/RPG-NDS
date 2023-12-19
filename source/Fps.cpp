#include "Fps.h"

#ifdef FPS_ENABLE
using namespace std;

Fps::Fps() {}
Fps::Fps(int updatesPerSeconds):m_frameCounter(0), m_fps(0), m_updatesPerSeconds(updatesPerSeconds)
{
	globalFps = this;
	timerStart(0, ClockDivider_1024, TIMER_FREQ_1024(m_updatesPerSeconds), updateGlobalFps);
}

Fps::~Fps() {}


void Fps::newFrame()
{
	m_frameCounter++;
	cout << "\x1b[23;26HFPS:" << setfill(' ') << setw(2) << m_fps << "\x1b[0;0H";
}

void Fps::update()
{
	m_fps = m_frameCounter*m_updatesPerSeconds;
	m_frameCounter = 0;
}

int Fps::getFps()
{
	return m_fps;
}

void updateGlobalFps()
{
	globalFps->update();
}

#endif