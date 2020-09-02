#ifndef LIGHT_H
#define LIGHT_H

#include <GL/glut.h>

class Light
{
	public:
		void initLight();
	private:
		float ambientColour[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		float diffuseColour[4] = { 0.7f, 0.7f, 0.7f, 1.0f };
		float specularColour[4] = { 1.0f, 1.0f, 1.0f, 1.0f };
		float position[4] = { 0.0f, 0.0f, 20.0f, 1.0f };
};

#endif
