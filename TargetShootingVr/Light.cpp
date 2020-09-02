#include "Light.h"

void Light::initLight() 
{
	// set up light colors (ambient, diffuse, specular)
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColour);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColour);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularColour);

	// position the light
	glLightfv(GL_LIGHT0, GL_POSITION, position);

	// MUST enable each light source after configuration
	glEnable(GL_LIGHT0);
}
