#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>

class Object
{
	public:
		virtual void drawObject() = 0;

	protected:
		float diffuseColour[3] = { 1.0, 1.0, 0.0 };
		float specularColour[3];
};

#endif
