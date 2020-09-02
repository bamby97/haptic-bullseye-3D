#ifndef SCENE_H
#define SCENE_H

#include "Camera.h"
#include "Target.h"
#include "Light.h"
#include "HapticManager.h"
#include "Projectile.h"
#include "Dart.h"
#include "InfoDisplay.h"
#include "Box.h"
#include "Logger.h"

class Scene {
	public:
		Scene();
		void createScene();
		void init();
		void toggleGameMode();
		void printInfo();
	private:
		Camera camera;
		Target outerTarget;
		Target innerTarget;
		Target middleTarget;
		Light light;
		Dart dart;
		Projectile projectile;
		Box box;
		InfoDisplay infoDisplay;
		HapticManager hapticManager;
		Logger logger;
		float targetDepth;
		void drawScene();
		int frameCount;
};

#endif
