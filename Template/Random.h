#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\glut.h"											// Header File For The OpenGL32 Library
#include "Vector3f.h"
#include "Texture.h"

using namespace std;

// random poer-up / down will have random effects such as speed and damage up or down
class Random
{
public:
	Random();
	Random(CVector3f pos);
	~Random();

	void Render(float dt);
	void Create();
	CVector3f GetPosition();

private:
	CVector3f position;	// position
	bool active;		// bool for rendering only active power-up / downs
	CTexture texture;	// texture for the mesh
	UINT textureId;		// holds texture id
}; 
