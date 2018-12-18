#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\include\gl.h"								// Header File For The OpenGL32 Library
#include "Vector3f.h"
#include "Texture.h"

class CSpriteExplosion
{
public:
	CSpriteExplosion();
	~CSpriteExplosion();
	bool Initialise(const char *filename, const int frameWidth, const int frameHeight, const int numFrames, bool loop);
	void Update(float dt);
	void Render(CVector3f p, CVector3f lookAt, CVector3f upVector, float width, float height);
	void Activate();
	bool Active();
private:
	
	bool m_active;
	bool m_loop;
	unsigned int m_frame;
	unsigned int m_totalFrames;
	float m_elapsedTime;

	unsigned int m_frameWidth;
	unsigned int m_frameHeight;

	unsigned int m_framesX;
	unsigned int m_framesY;

	
	CTexture m_texture;

};