#pragma once
#include <windows.h>
#include ".\include\gl.h"			
#include ".\include\glut.h"	
#include "Vector3f.h"
#include "Texture.h"
#include "HeightMapTerrain.h"

using namespace std;

// Power-up that will make the player invisible to monsters for a short period of time
class Grass
{
public:
	Grass();
	Grass(CVector3f pos);
	~Grass();

	void Render(CTexture* texture);
	void Create();
	CVector3f GetPosition();
	int GetType();
	float rot;

private:
	CVector3f position;	//position
	int type;

	//CTexture texture1;	// texture for the mesh
	//UINT m_textureID1;	// holds the texture Id
	//CTexture texture2;	// texture for the mesh
	//UINT m_textureID2;	// holds the texture Id
};