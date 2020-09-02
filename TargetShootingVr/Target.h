#ifndef TARGET_H
#define TARGET_H

#include "Object.h"
#include <math.h>
#include <iostream>
using namespace std;


class Target: public Object
{
	public:
		Target(float radius, float opacity, float x, float y, float z);
		virtual void drawObject() override;
		void handleCollision(float x, float y, float z);
		bool Target::shouldUpdateScore();
		void setDepth(float depth);
		float getDepth();

	private:
		float radius;
		bool Target::isHit(float x, float y, float z);
		bool targetHit;
		float distance(float x, float y, float z);
		float position[3];
		bool changeColour;
		bool updateScore;
		bool toggleColour;
		float opacity;
};

#endif
