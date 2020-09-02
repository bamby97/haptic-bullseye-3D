#include "Timer.h"

Timer::Timer()
{
	// omitting error check for hardware that doesn’t support this.
	QueryPerformanceFrequency(&frequency); // get number of ticks per second
	running = false;
	delay = 60000;
}

void Timer::setTimeout(int msDelay)
{
	delay = msDelay;
}

void Timer::start()
{
	QueryPerformanceCounter(&startTime);
	running = true;
}

void Timer::stop()
{
	running = false;
}

bool Timer::isRunning()
{
	return running;
}

float Timer::getElapsedTime()
{
	if (!running)
		return 0;
	float remainingTime;
	LARGE_INTEGER now;
	QueryPerformanceCounter(&now);

	LARGE_INTEGER ElapsedMilliseconds;
	ElapsedMilliseconds.QuadPart = now.QuadPart - startTime.QuadPart;

	ElapsedMilliseconds.QuadPart *= 1000000;
	ElapsedMilliseconds.QuadPart /= frequency.QuadPart; // now microseconds
	ElapsedMilliseconds.QuadPart /= 1000; // milliseconds

	bool fExpired = (ElapsedMilliseconds.HighPart > 0 || ElapsedMilliseconds.LowPart >= delay);
	
	if (fExpired)
	{
		running = false;
		return 0;
	}

	remainingTime = (float(delay) - ElapsedMilliseconds.QuadPart)/1000.0f;
	
	return remainingTime;
}
