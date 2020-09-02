#include "Box.h"

void Box::drawObject()
{
	glPushMatrix();
		glTranslatef(0.0, 0.0, 6.0);
		glScalef(1.5, 1.5, 4.0);
		glColor3f(1.0, 0.0, 0.0);
		glLineWidth(5.0);
		glutWireCube(1.0);
	glPopMatrix();
}
