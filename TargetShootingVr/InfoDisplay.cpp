#include "InfoDisplay.h"


InfoDisplay::InfoDisplay()
{
	score = 0;
	timerStarted = false;
	isGameOver = false;
}

bool InfoDisplay::isOver()
{
	return isGameOver;
}

void InfoDisplay::showTimer(bool startTimer) {
	glPushMatrix();    // save current modelview matrix
	glLoadIdentity();  // reset modelview matrix

									// set to 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);    // switch to projection matrix
	glPushMatrix();                 // save current projection matrix
	glLoadIdentity();               // reset projection matrix
	gluOrtho2D(0, 400, 0, 300);     // set to orthogonal projection

	float color[4] = { 1, 1, 1, 1 };


	stringstream ss;
	ss << std::fixed;
	
	if (startTimer&&!timer.isRunning()&&!timerStarted) {
		timer.start();
		timerStarted = true;
	}
	
	// display elapsed time in millisec
	ss << "Timer: " << std::setprecision(1) << timer.getElapsedTime() << " sec(s)" << ends;
	drawString(ss.str().c_str(), 330, 272, color, GLUT_BITMAP_TIMES_ROMAN_24);
	ss.str("");
	
	// restore projection matrix
	glPopMatrix();

    // restore modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

float InfoDisplay::getTime()
{
	return timer.getElapsedTime();
}

void InfoDisplay::showScore() {
	
	glPushMatrix();                     // save current modelview matrix
	glLoadIdentity();                   // reset modelview matrix

										// set to 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);        // switch to projection matrix
	glPushMatrix();                     // save current projection matrix
	glLoadIdentity();                   // reset projection matrix
	gluOrtho2D(0, 400, 0, 300);         // set to orthogonal projection

	float color[4] = { 1, 1, 1, 1 };


	stringstream ss;
	ss << std::fixed;

	// display elapsed time in millisec
	if (timer.isRunning()) {
		ss << "Score: " << this->score << ends;
		drawString(ss.str().c_str(), 8, 272, color, GLUT_BITMAP_TIMES_ROMAN_24);
		ss.str("");
		finalScore = score;
	}
	if(!timer.isRunning()&&timerStarted) {
		ss << "Time out! Your score was: " << finalScore << ends;
		drawString(ss.str().c_str(), 160, 272, color, GLUT_BITMAP_TIMES_ROMAN_24);
		ss.str("");
		isGameOver = true;
	}


	// restore projection matrix
	glPopMatrix();

	// restore modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glPopMatrix();
}

void InfoDisplay::updateScore(int value)
{
	if (timer.isRunning()) {
		score += value;
	}
}

int InfoDisplay::getFinalScore()
{
	return score;
}

void InfoDisplay::drawString(const char *str, int x, int y, float color[4], void *font) {
	glPushAttrib(GL_LIGHTING_BIT | GL_CURRENT_BIT); // lighting and color mask
	glDisable(GL_LIGHTING);     // need to disable lighting for proper text color

	glColor4fv(color);          // set text color
	glRasterPos2i(x, y);        // place text position

								// loop all characters in the string
	while (*str)
	{
		glutBitmapCharacter(font, *str);
		++str;
	}

	glEnable(GL_LIGHTING);
	glPopAttrib();
}


void InfoDisplay::showMessage(string message) {

	glPushMatrix();                     // save current modelview matrix
	glLoadIdentity();                   // reset modelview matrix

										// set to 2D orthogonal projection
	glMatrixMode(GL_PROJECTION);        // switch to projection matrix
	glPushMatrix();                     // save current projection matrix
	glLoadIdentity();                   // reset projection matrix
	gluOrtho2D(0, 400, 0, 300);         // set to orthogonal projection

	float color[4] = { 1, 1, 1, 1 };

	drawString(message.c_str(), 157, 250, color, GLUT_BITMAP_TIMES_ROMAN_24);

	// restore projection matrix
	glPopMatrix();                   // restore to previous projection matrix

									 // restore modelview matrix
	glMatrixMode(GL_MODELVIEW);      // switch to modelview matrix
	glPopMatrix();
}
