#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\glut.h"											// Header File For The OpenGL32 Library
#include "Vector3f.h"
#include "Texture.h"

class CAlphaSphere
{
public:
	CAlphaSphere();
	~CAlphaSphere();
	void Activate(float radius, CVector3f startColour, CVector3f endColour, bool zap, float zapLevel, CVector3f pos);
	void Update(float dt);
	void Render();
	bool Active();
	float GetCurrentRange();
	CVector3f GetOrigin();

private:

	float Random();

	CVector3f mpvPosition;
	float m_radius;
	bool m_isActive;
	float m_totalTime;
	float m_elapsedTime;
	float m_zapLevel;

	CVector3f m_startColour;
	CVector3f m_endColour;
	CVector3f m_colour;
	bool m_zap;

	
};