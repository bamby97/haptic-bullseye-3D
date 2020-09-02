#ifndef TIMER_H_DEF
#define TIMER_H_DEF
#include <windows.h>
#include <iostream>

#include <ctime>
using namespace std;

class Timer
{
public:
	Timer();


	void    setTimeout(int msDelay);
	void    start();
	void    stop();
	bool    isRunning();
	// Has the timer expired since the last poll
	float    getElapsedTime();

private:
	LARGE_INTEGER startTime;
	LARGE_INTEGER frequency; // per second
	int     delay; // in milliseconds
	bool    running;
};
#endif 
