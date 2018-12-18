#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include "Texture.h"
#include "Vector3f.h"
#include <vector>


class CCrossFade
{
public:
	CCrossFade();
	~CCrossFade();
	void Activate();
	void Render(float red, float green, float blue);
	void Update(float dt);
	bool Active();
private:

	void SetOrthographicProjection();
	void RestorePerspectiveProjection();
	GLint m_viewport[4];

	bool m_isActive;
	float m_elapsedTime;
	float m_totalTime;
	float m_alpha;

	
};