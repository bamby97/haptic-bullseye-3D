#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "Object.h"
#include <HL/hl.h>

class Projectile: Object
{
	public:
		Projectile(double scale);
		virtual void drawObject() override;
		void setProjectileSize(double size);
		void animate();
		bool isOutOfBounds();
		bool shouldShoot();
		float* getPosition();
		float* getThrowPosition();
		void reset();
		bool isThrown();
		bool thrown;
		float* getThrowVelocity();
	private:
		bool shoot;
		bool released;
		HLdouble lastPosition[16];
		float position[3];
		double projectileScale;
		float deltaT;
		HDdouble lastVelocity[3];
		HDdouble velocity[3];
		bool resetPosition;
		HLdouble throwPosition[16];
		float positionThrow[3];
		float velocityThrow[3];
};

#endif

