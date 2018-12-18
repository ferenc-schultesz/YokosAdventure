#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include "Texture.h"
#include "Vector3f.h"

#include <vector>

class CLightningBolt
{
public:
	CLightningBolt();
	~CLightningBolt();
	bool ComputePath(CVector3f p0, CVector3f dir);
	void Render();
	void Update(float dt);
	void Activate();

private:
	void RenderLineSegment(CVector3f p0, CVector3f p1, float alpha, CVector3f colour);
	std::vector<CVector3f> m_points;
	bool m_isActive;
	float m_elapsedTime;
	float m_totalTime;
	
};