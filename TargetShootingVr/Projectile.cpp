#include "Projectile.h"
#include <iostream>
using namespace std;

Projectile::Projectile(double scale)
{
	deltaT = 0.001;
	projectileScale = scale;
	shoot = false;
	released = false;
	velocity[1] = 0.0;
	resetPosition = false;
	thrown = false;

	for (int i = 0; i < 16; i++) 
	{
		// initialize to dummy number to avoid memory errors
		lastPosition[i] = -100.0;
	}

	for (int i = 0; i < 16; i++)
	{
		// initialize to dummy number to avoid memory errors
		throwPosition[i] = -100.0;
	}
}

void Projectile::setProjectileSize(double size)
{
	projectileScale *= size;
}

void Projectile::reset()
{
	resetPosition = true;
}

float* Projectile::getPosition()
{
	position[0] = lastPosition[12];
	position[1] = lastPosition[13];
	position[2] = lastPosition[14];

	return position;
}

float* Projectile::getThrowPosition()
{	
	positionThrow[0] = throwPosition[12];
	positionThrow[1] = throwPosition[13];
	positionThrow[2] = throwPosition[14];

	return positionThrow;

}

float* Projectile::getThrowVelocity()
{
	return velocityThrow;
}

void Projectile::animate()
{
	if (released == true) {
		lastPosition[12] += (lastVelocity[0] / 10.0) * deltaT;
		
		//change y velocity and position - y velocity changes due to gravity
		velocity[1] -= (9.81 * deltaT);
		lastPosition[13] += (velocity[1] * deltaT);

		lastPosition[14] += (lastVelocity[2] / 10.0) * deltaT;
	}
}

void Projectile::drawObject()
{	
	HLdouble proxyxform[16];
	hlGetDoublev(HL_PROXY_TRANSFORM, proxyxform);

	glPushMatrix();
		if (shouldShoot() == true) {
			shoot = true;
		}
		else if (isOutOfBounds() == true || resetPosition == true) {
			shoot = false;
			released = false;
			resetPosition = false;
		}

		if (shoot == true) {
			if (released == false) {
				thrown = true;
				hlGetDoublev(HL_PROXY_TRANSFORM, lastPosition);
				hdGetDoublev(HD_CURRENT_VELOCITY, lastVelocity);
				hlGetDoublev(HL_PROXY_TRANSFORM, throwPosition);
				velocityThrow[0] = lastVelocity[0];
				velocityThrow[1] = lastVelocity[1];
				velocityThrow[2] = lastVelocity[2];
				velocity[1] = lastVelocity[1]/10.0;
				released = true;
			}
			else {
				thrown = false;
			}
			glMultMatrixd(lastPosition);
		} else {
			glMultMatrixd(proxyxform);
		}

		glScaled(projectileScale, projectileScale, projectileScale);
		glColor3f(1.0, 0.0, 0.0);
		glutSolidSphere(1.0, 16.0, 16.0);

	glPopMatrix();
}

bool Projectile::shouldShoot()
{
	HDdouble maxVel = 300.0;
	HDdouble velocity[3];
	hdGetDoublev(HD_CURRENT_VELOCITY, velocity);

	HDdouble x = velocity[0];
	HDdouble y = velocity[1];
	HDdouble z = velocity[2];

	if (x < -maxVel || x> maxVel || y < -maxVel || y > maxVel || z < -maxVel) {
		return true;
	}
	
	return false;
}

bool Projectile::isOutOfBounds()
{
	HLdouble x = lastPosition[12];
	HLdouble y = lastPosition[13];
	HLdouble z = lastPosition[14];
	
	if (z < -50.0 || z > 50.0 || y > 30.0 || y < -30.0 || x > 30.0 || x < -30.0)
	{
		return true;
	}

	return false;
}

bool Projectile::isThrown()
{
	return thrown;
}
