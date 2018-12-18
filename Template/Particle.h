#pragma once
#include <windows.h>								// Header File For The Windows Library
#include ".\gl\gl.h"								// Header File For The OpenGL32 Library
#include "Vector3f.h"

class CParticle
{
public:
	CParticle();
	~CParticle();
	bool Initialise(CVector3f pIn, float widthIn, float heightIn, CVector3f startColour, CVector3f endColour, float transitionSpeed);
	void Render(CVector3f lookAt, CVector3f upVector);
	void Update(float dt);
	bool IsAlive();

private:
	float m_life;
	CVector3f m_position;
	CVector3f m_velocity;

	float m_width;
	float m_height;

	float m_angle;
	float m_angularVelocity;

	CVector3f m_startColour;
	CVector3f m_endColour;
	float m_transitionSpeed;

};