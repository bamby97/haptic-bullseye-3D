#ifndef DART_H
#define DART_H
#include "Object.h"
#include <HL/hl.h>
#include <HDU/hduMatrix.h>
#include <HDU/hduError.h>
#include <HLU/hlu.h>


class Dart: public Object
{
	public:
		Dart(double scale);
		virtual void drawObject() override;
		void setDartSize(double size);
		bool shouldBeginGame();
	private:
		double dartScale;
		GLuint dartDisplayList;
		double kDartRadius;
		double kDartHeight;
		int kDartTess;
		bool beginGame;
		hduVector3Dd devicePosition;
};

#endif
