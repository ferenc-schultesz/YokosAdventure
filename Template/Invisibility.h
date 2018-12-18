#pragma once
#include <windows.h>
#include ".\include\gl.h"			
#include ".\include\glut.h"	
#include "Vector3f.h"
#include "Texture.h"
#include "HeightMapTerrain.h"
#include "BoundingBox.h"

using namespace std;

// Power-up that will make the player invisible to monsters for a short period of time
class Invisibility
{
public:
	Invisibility();
	Invisibility(CVector3f pos, HeightMapTerrain* heightmap);
	~Invisibility();

	void Render(float dt, CTexture* texture);
	void Create();
	CVector3f GetPosition();
	bool Active();
	CBoundingBox* BBox();
	void Destroy();

private:
	CVector3f position;	//position
	bool active;		// bool for rendering only active power-ups
	CTexture texture;	// texture for the mesh
	UINT m_textureID;	// holds the texture Id
	HeightMapTerrain* hm;
	CBoundingBox m_bbox;
};