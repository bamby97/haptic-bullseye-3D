#ifndef INFODISPLAY_H_DEF
#define INFODISPLAY_H_DEF
#include <iostream>
#include <sstream>
#include "Timer.h"
#include <iostream>
#include <iomanip>
#include <stdlib.h>
#include <GL/glut.h>

using namespace std;

class InfoDisplay
{
public:
	InfoDisplay();
	void showTimer(bool startTimer);
	 void showScore();
	 void updateScore(int value);
	 void showMessage(string message);
	 float getTime();
	 bool isOver();
	 int getFinalScore();
private:
	Timer timer;
	int score, finalScore;
	bool timerStarted;
	void drawString(const char *str, int x, int y, float color[4], void *font);
	bool isGameOver;
};
#endif
