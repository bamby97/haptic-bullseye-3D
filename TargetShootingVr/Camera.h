#ifndef CAMERA_H
#define CAMERA_H

#include <math.h>
#include <GL/glut.h>

#define DTOR            0.0174532925   // DEGREE TO RADIAN

typedef struct 
{
	double x, y, z;
} XYZ;

class Camera
{
	public:
		Camera::Camera(double aperture, double focalLength, double vpx, double vpy, double vpz, double vdx, double vdy, double vdz, double vux, double vuy, double vuz);
		void drawRightCamera();
		void drawLeftCamera();

	private:
		XYZ vp;              /* View position           */
		XYZ vd;              /* View direction vector   */
		XYZ vu;              /* View up direction       */
		double focalLength;  /* Focal Length along vd   */
		double aperture;     /* Camera aperture         */
		double eyeSep;       /* Eye separation - interpupilar distance    */
		float nearP;
		float farP;
		float wd2;
		float ndfl;
		XYZ r;

		void normalise(XYZ *p);
		XYZ crossProduct(XYZ p1, XYZ p2);
};

#endif
