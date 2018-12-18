#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\glut.h"											// Header File For The OpenGL32 Library
#include "Vector3f.h"
#include "Texture.h"
#include "BoundingBox.h"
#include "HeightMapTerrain.h"

using namespace std;

// Health and mana potions for the game built from primitives
class Potion
{
public:
	Potion();
	Potion(CVector3f pos, string type, HeightMapTerrain* heightmap); // type: health, mana
	~Potion();

	void Render(float dt, CTexture * texture);
	void Create();

	CVector3f GetPosition();
	string GetType();
	bool Active();
	float Mana();
	float Health();
	CBoundingBox* BBox();
	void Destroy();
private:
	CVector3f position;		// position in world coordinates
	bool active;			// bool for rendering only active potions
	CTexture m_texture;	// texture for the mesh
	UINT m_textureID;		// texture id for rendering
	string type;			// mana or health
	float mana;
	float health;
	CBoundingBox m_bbox;
	HeightMapTerrain* hm;
};
