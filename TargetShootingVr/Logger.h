#ifndef LOGGER_H
#define LOGGER_H

#include <iostream>
#include <fstream>
#include <vector>
#include <iomanip>
using namespace std;

struct gameInfo {
	bool hitTarget;
	float timeRemaining;
	float projectilePosition[3];
	float projectileVelocity[3];
	float targetDepth;
	int throwNumber;
	int addedScore;
	int targetHit;
};

class Logger
{
	public:
		gameInfo info;
		void pushInfo();
		void printInfo();
		void setTotalScore(int score);
		void setFrameCount(float count);
		Logger();
	private:
		ofstream myfile;
		vector<gameInfo> gameData;
		int totalScore;
		int frameCount;
};
#endif
