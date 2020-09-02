#include "Dart.h"

Dart::Dart(double scale)
{
	dartScale = scale;
	GLuint dartDisplayList;
	kDartRadius = 0.5;
	kDartHeight = 1.5;
	kDartTess = 15;
	beginGame = false;
}

void Dart::drawObject()
{
	HLdouble proxyxform[16];

	GLUquadricObj *qobj = 0;

	glPushAttrib(GL_CURRENT_BIT | GL_ENABLE_BIT | GL_LIGHTING_BIT);
	glPushMatrix();

	if (!dartDisplayList)
	{
		dartDisplayList = glGenLists(1);
		glNewList(dartDisplayList, GL_COMPILE);
		qobj = gluNewQuadric();

		gluCylinder(qobj, 0.0, kDartRadius, kDartHeight,
			kDartTess, kDartTess);
		glTranslated(0.0, 0.0, kDartHeight);
		gluCylinder(qobj, kDartRadius, 0.0, kDartHeight / 5.0,
			kDartTess, kDartTess);

		gluDeleteQuadric(qobj);
		glEndList();
	}

	// Get the proxy transform in world coordinates for haptic device.
	hlGetDoublev(HL_PROXY_TRANSFORM, proxyxform);
	glMultMatrixd(proxyxform);

	// Apply the local cursor scale factor.
	glScaled(dartScale, dartScale, dartScale * 2);

	glColor3f(0.0, 0.5, 1.0);

	glCallList(dartDisplayList);

	glPopMatrix();
	glPopAttrib();
}

void Dart::setDartSize(double size)
{
	dartScale *= size;
}

bool Dart::shouldBeginGame() {
	if (beginGame == false) {
		hdGetDoublev(HD_CURRENT_POSITION, devicePosition);
		if (devicePosition[1] < 35 && devicePosition[1]>13) {
			if (devicePosition[2] > -43 && devicePosition[2]<-5) {
				if (devicePosition[0] > -6 && devicePosition[0]<10) {
					beginGame = true;
				}
			}
		}
	}
	return beginGame;
}
