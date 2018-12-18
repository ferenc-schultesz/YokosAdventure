#pragma once

#include <math.h>
#include <string.h>
#include <stdlib.h>
#include ".\include\glut.h"	
#include <Windows.h>

class CText
{
public:
	CText();
	~CText();
	void Render(float x, float y, float r, float g, float b, char *text, ...);
	void Create(HDC hdc, char *fontName, int size);

private:
	void SetOrthographicProjection();
	void ResetPerspectiveProjection();
	void RenderBitmapString(float x, float y, char *string);
};

