#include "HapticManager.h"

HapticManager::HapticManager()
{
	ghHD = HD_INVALID_HANDLE;
	ghHLRC = 0;
	targetId = hlGenShapes(1);
	app2 = false;
	app2started = false;
}

void HapticManager::initHL()
{
	HDErrorInfo error;

	ghHD = hdInitDevice(HD_DEFAULT_DEVICE);
	if (HD_DEVICE_ERROR(error = hdGetError()))
	{
		hduPrintError(stderr, &error, "Failed to initialize haptic device");
		fprintf(stderr, "Press any key to exit");
		getchar();
		exit(-1);
	}

	ghHLRC = hlCreateContext(ghHD);
	hlMakeCurrent(ghHLRC);

	// Enable optimization of the viewing parameters when rendering
	// geometry for OpenHaptics.
	hlEnable(HL_HAPTIC_CAMERA_VIEW);
	limitingBoxId = hlGenShapes(1);

	hlTouchableFace(HL_BACK);
	initWorkSpace();
}

void HapticManager::toggleGameMode()
{
	app2 = !app2;
}

void HapticManager::initWorkSpace()
{
	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	hlMatrixMode(HL_TOUCHWORKSPACE);

	HLdouble minPoint[3], maxPoint[3];
	minPoint[0] = -10;
	minPoint[1] = -10;
	minPoint[2] = -10;
	maxPoint[0] = 10;
	maxPoint[1] = 10;
	maxPoint[2] = 10;
	hluFitWorkspaceBox(modelview, minPoint, maxPoint);
}

double HapticManager::getWorkSpaceScale()
{
	return hluScreenToModelScale(modelview, projection, viewport);
}

void HapticManager::drawSceneHaptics()
{
	// Start haptic frame.  (Must do this before rendering any haptic shapes.)
	hlBeginFrame();

	// Set material properties for the shapes to be drawn.
	hlMaterialf(HL_FRONT_AND_BACK, HL_STIFFNESS, 0.7f);
	hlMaterialf(HL_FRONT_AND_BACK, HL_DAMPING, 0.1f);
	hlMaterialf(HL_FRONT_AND_BACK, HL_STATIC_FRICTION, 0.2f);
	hlMaterialf(HL_FRONT_AND_BACK, HL_DYNAMIC_FRICTION, 0.3f);
	// Start a new haptic shape.  Use the feedback buffer to capture OpenGL 
	// geometry for haptic rendering.
	hlBeginShape(HL_SHAPE_FEEDBACK_BUFFER, limitingBoxId);

	// Use OpenGL commands to create geometry.
	glPushMatrix();

	drawBox();

	glPopMatrix();

	// End the shape.
	hlEndShape();

	if (app2 == true)
	{
		if (!app2started) {
			myEffectId = hlGenEffects(1);
			static const HDdouble position[3] = { 2, 26, -24 };
			hlEffectdv(HL_EFFECT_PROPERTY_POSITION, position);
			hlEffectd(HL_EFFECT_PROPERTY_GAIN, 0.4);
			hlEffectd(HL_EFFECT_PROPERTY_MAGNITUDE, 0.4);
			hlStartEffect(HL_EFFECT_SPRING, myEffectId);
		}
		
		app2started = true;
	}
	else if (app2started == true) {
		hlStopEffect(myEffectId);
		hlDeleteEffects(myEffectId, 1);
		app2started = false;
	}
	
	// End the haptic frame.
	hlEndFrame();
}
void HapticManager::drawBox() {
	glTranslatef(0.0, 0.0, 6.0);
	glScalef(1.5, 1.5, 4.0);
	glColor3f(1.0, 0.0, 0.0);
	glLineWidth(5.0);
	glutSolidCube(1.0);
}
