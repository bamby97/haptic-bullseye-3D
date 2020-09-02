#ifndef HAPTIC_H
#define HAPTIC_H

#include <HL/hl.h>
#include <HDU/hduMatrix.h>
#include <HDU/hduError.h>
#include <HLU/hlu.h>
#include <GL/glut.h>

class HapticManager
{
	public:
		HapticManager();
		void initHL();
		void initWorkSpace();
		void drawSceneHaptics();
		double getWorkSpaceScale();
		void toggleGameMode();
	private:
		void drawBox();
		HHD ghHD;
		HHLRC ghHLRC;
		HLuint targetId,limitingBoxId;
		GLdouble modelview[16];
		GLdouble projection[16];
		GLint viewport[4];
		bool app2;
		HLuint myEffectId;
		bool app2started;
};

#endif
