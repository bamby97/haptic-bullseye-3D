#include "Scene.h"

Scene::Scene() : camera(60, 14, 0, 0, 10, 0, 0, -1, 0, 1, 0), outerTarget(1.0, 0.5, 0.0, 0.0, 0.0), innerTarget(0.5, 0.8, 0.0, 0.0, 0.0), middleTarget(0.8, 0.5, 0.0, 0.0, 0.0), projectile(30), dart(60)
{
	targetDepth = 0.0;
	frameCount = 0;
}

void Scene::createScene() {
	light.initLight();
	camera.drawRightCamera();
	projectile.animate();
	drawScene();
	glFlush();

	camera.drawLeftCamera();
	drawScene();
	glFlush();

	hapticManager.drawSceneHaptics();

	if (dart.shouldBeginGame() == true && infoDisplay.isOver() == false)
	{
		frameCount++;
	}
}

void Scene::toggleGameMode()
{
	hapticManager.toggleGameMode();
}

void Scene::drawScene() 
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
	
	float * projectilePosition = projectile.getPosition();

	outerTarget.handleCollision(projectilePosition[0], projectilePosition[1], projectilePosition[2]);
	outerTarget.drawObject();
	
	innerTarget.handleCollision(projectilePosition[0], projectilePosition[1], projectilePosition[2]);
	innerTarget.drawObject();

	middleTarget.handleCollision(projectilePosition[0], projectilePosition[1], projectilePosition[2]);
	middleTarget.drawObject();

	infoDisplay.showScore();
	
	if (dart.shouldBeginGame() == true) {
		infoDisplay.showTimer(true);
	}
	else {
		infoDisplay.showMessage("Move the dart inside the box to begin the game");
		infoDisplay.showTimer(false);
	}

	dart.drawObject();
	projectile.drawObject();
	box.drawObject();

	if (infoDisplay.isOver() == false) {
		if (outerTarget.shouldUpdateScore() == true)
		{
			infoDisplay.updateScore(50);
			
			logger.info.targetHit = 1;
			logger.info.hitTarget = true;
			logger.info.timeRemaining = infoDisplay.getTime();
			logger.info.targetDepth = outerTarget.getDepth();
			logger.info.addedScore = 50;
			logger.setTotalScore(infoDisplay.getFinalScore());
			logger.pushInfo();
		}
		else if (middleTarget.shouldUpdateScore() == true) {
			infoDisplay.updateScore(50);
			
			logger.info.targetHit = 2;
			logger.info.hitTarget = true;
			logger.info.timeRemaining = infoDisplay.getTime();
			logger.info.targetDepth = middleTarget.getDepth();
			logger.info.addedScore = 50;
			logger.setTotalScore(infoDisplay.getFinalScore());
			logger.pushInfo();
		}
		else if (innerTarget.shouldUpdateScore() == true) {
			targetDepth -= 2.0;
			infoDisplay.updateScore(100);
			
			logger.info.targetHit = 3;
			logger.info.hitTarget = true;
			logger.info.timeRemaining = infoDisplay.getTime();
			logger.info.targetDepth = innerTarget.getDepth();
			logger.info.addedScore = 100;
			logger.setTotalScore(infoDisplay.getFinalScore());
			logger.pushInfo();
			
			// stop target from moving away in the z-direction at a certain limit
			if (targetDepth > -32.0)
			{
				innerTarget.setDepth(targetDepth);
				middleTarget.setDepth(targetDepth);
				outerTarget.setDepth(targetDepth);
				projectile.reset();
			}
		}
		else if (projectile.isThrown() == true)
		{
			logger.info.throwNumber += 1;
			logger.info.timeRemaining = infoDisplay.getTime();
			logger.info.targetDepth = innerTarget.getDepth();
			
			float * throwPosition = projectile.getThrowPosition();
			
			logger.info.projectilePosition[0] = throwPosition[0];
			logger.info.projectilePosition[1] = throwPosition[1];
			logger.info.projectilePosition[2] = throwPosition[2];

			float * throwVelocity = projectile.getThrowVelocity();

			logger.info.projectileVelocity[0] = throwVelocity[0];
			logger.info.projectileVelocity[1] = throwVelocity[1];
			logger.info.projectileVelocity[2] = throwVelocity[2];
			
			logger.pushInfo();
		}
	}

	glFlush();
}

void Scene::init()
{
	hapticManager.initHL();
	double scale = hapticManager.getWorkSpaceScale();
	dart.setDartSize(scale);
	projectile.setProjectileSize(scale);
}

void Scene::printInfo()
{
	logger.setFrameCount(frameCount);
	logger.printInfo();
}
