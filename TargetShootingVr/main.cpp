#include <stdlib.h>
#include <GL/glut.h>
#include "Scene.h"

// function declarations
int initGLUT(int argc, char **argv);
void initGL();
void displayCB();
void idleCB();
void keyboardCB(unsigned char key, int x, int y);

//global variables
Scene scene;

int main(int argc,char **argv)
{	
	// init GLUT and GL
	initGLUT(argc, argv);
	initGL();
	scene.init();

	// the last GLUT call (LOOP)
	// window will be shown and display callback is triggered by events
	// NOTE: this call never return main().
	glutMainLoop(); /* Start GLUT event-processing loop */

	return 0;
}

int initGLUT(int argc, char **argv)
{
	// GLUT stuff for windowing
	// initialization openGL window.
	// it is called before any other GLUT routine
	glutInit(&argc, argv);

	// display stereo mode
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH | GLUT_STENCIL | GLUT_STEREO);   

	// window size
	glutInitWindowSize(400, 300);              

	// window location
	glutInitWindowPosition(100, 100);           

	// finally, create a window with openGL context
	// Window will not displayed until glutMainLoop() is called
	// it returns a unique ID
	// param is the title of window
	int handle = glutCreateWindow(argv[0]);     
	glutFullScreen();

	//callbacks
	glutDisplayFunc(displayCB);
	glutIdleFunc(idleCB);
	glutKeyboardFunc(keyboardCB);

	return handle;
}

void initGL()
{
	glShadeModel(GL_SMOOTH);                    // shading method: GL_SMOOTH or GL_FLAT
	glPixelStorei(GL_UNPACK_ALIGNMENT, 4);      // 4-byte pixel alignment

	// enable /disable features
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);

	// track material ambient and diffuse from surface color, call it before glEnable(GL_COLOR_MATERIAL)
	glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
	glEnable(GL_COLOR_MATERIAL);

	glClearColor(0, 0, 0.3, 0);                  // background color blue
	glClearStencil(0);                          // clear stencil buffer
	glClearDepth(1.0f);                         // 0 is near, 1 is far
	glDepthFunc(GL_LEQUAL);
}

void displayCB()
{
	scene.createScene();
	glutSwapBuffers();
}

void idleCB() {
	glutPostRedisplay();
}

void keyboardCB(unsigned char key, int x, int y)
{
	switch (key)
	{
	case 27: // ESCAPE
		scene.printInfo();
		exit(0);
		break;
	case ' ':
		scene.toggleGameMode();
		break;

	default:
		;
	}
}
