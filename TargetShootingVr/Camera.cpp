#include "Camera.h"
#include <stdio.h>

Camera::Camera(double aperture, double focalLength, double vpx, double vpy, double vpz, double vdx, double vdy, double vdz, double vux, double vuy, double vuz)
{
	this -> aperture = aperture;
	this -> focalLength = focalLength;
	vp.x = vpx;
	vp.y = vpy;
	vp.z = vpz;
	vd.x = vdx;
	vd.y = vdy;
	vd.z = vdz;
	vu.x = vux;
	vu.y = vuy;
	vu.z = vuz;
	this->eyeSep = focalLength / 60;

	nearP = 1.0;
	farP = 40.0;
	float radians = DTOR * aperture / 2;
	wd2 = nearP * tan(radians);
	ndfl = nearP / focalLength;

	r = crossProduct(vd, vu);
	// direction btw 2 cameras (right and left eyes, respectively) 
	normalise(&r);
	r.x *= eyeSep / 2.0;
	r.y *= eyeSep / 2.0;
	r.z *= eyeSep / 2.0;
}


void Camera::drawRightCamera() 
{
	// draw right eye - camera 1
	glDrawBuffer(GL_BACK_RIGHT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = 1.777;
	float left = -ratio * wd2 - 0.5 * eyeSep * ndfl;
	float right = ratio * wd2 - 0.5 * eyeSep * ndfl;
	float top = wd2;
	float bottom = -wd2;
	glFrustum(left, right, bottom, top, nearP, farP);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(vp.x + r.x, vp.y + r.y, vp.z + r.z,
		vp.x + r.x + vd.x,
		vp.y + r.y + vd.y,
		vp.z + r.z + vd.z,
		vu.x, vu.y, vu.z);
}

void Camera::drawLeftCamera() 
{
	// draw left eye - camera 2
	glDrawBuffer(GL_BACK_LEFT);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float ratio = 1.777;
	float left = -ratio * wd2 + 0.5 * eyeSep * ndfl;
	float right = ratio * wd2 + 0.5 * eyeSep * ndfl;
	float top = wd2;
	float bottom = -wd2;
	glFrustum(left, right, bottom, top, nearP, farP);

	glMatrixMode(GL_MODELVIEW);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();
	gluLookAt(vp.x - r.x, vp.y - r.y, vp.z - r.z,
		vp.x - r.x + vd.x,
		vp.y - r.y + vd.y,
		vp.z - r.z + vd.z,
		vu.x, vu.y, vu.z);
}

void Camera::normalise(XYZ *p)
{
	double length = sqrt(p->x * p->x + p->y * p->y + p->z * p->z);

	if (length != 0) {
		p->x /= length;
		p->y /= length;
		p->z /= length;
	}
	else {
		p->x = 0;
		p->y = 0;
		p->z = 0;
	}
}

XYZ Camera::crossProduct(XYZ p1, XYZ p2) 
{
	XYZ p3;

	p3.x = p1.y*p2.z - p1.z*p2.y;
	p3.y = p1.z*p2.x - p1.x*p2.z;
	p3.z = p1.x*p2.y - p1.y*p2.x;
	
	return p3;
}
