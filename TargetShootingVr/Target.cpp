#include "Target.h"

Target::Target(float radius, float opacity,  float x, float y, float z)
{
	this->radius = radius;
	this->opacity = opacity;
	targetHit = false;
	changeColour = true;
	position[0] = x;
	position[1] = y;
	position[2] = z;
	updateScore = false;
	toggleColour = false;
}

void Target::setDepth(float depth)
{
	position[2] = depth;
}

float Target::getDepth()
{
	return position[2];
}

void Target::drawObject() 
{
	glPushMatrix();
		if (targetHit == true && changeColour == true)
		{
			toggleColour =! toggleColour;

			if (toggleColour == true) {
				diffuseColour[0] = 1.0;
				diffuseColour[1] = 0.0;
				diffuseColour[2] = 1.0;
			} else {
				diffuseColour[0] = 1.0;
				diffuseColour[1] = 1.0;
				diffuseColour[2] = 0.0;
			}

			changeColour = false;
			updateScore = true;
		}
		else
		{
			updateScore = false;
		}

		glTranslatef(position[0], position[1], position[2]);
		glDepthMask(GL_FALSE);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(diffuseColour[0], diffuseColour[1], diffuseColour[2], opacity);
		glutSolidSphere(radius, 20, 16);
		glDepthMask(GL_TRUE);
		glDisable(GL_BLEND);
	glPopMatrix();
}

bool Target::isHit(float x, float y, float z) 
{
	if (abs(distance(x, y, z) < radius)) 
	{
		return true;
	}
	
	return false;
}

void Target::handleCollision(float x, float y, float z)
{
	if (isHit(x, y, z) == true)
	{
		targetHit = true;
	}
	else 
	{
		targetHit = false;
		changeColour = true;
	}
}

bool Target::shouldUpdateScore()
{
	return updateScore;
}

float Target::distance(float x, float y, float z)
{
	return sqrt(pow(x-position[0], 2) + pow(y-position[1], 2) + pow(z-position[2], 2));
}
