#pragma once
#include <windows.h>									// Header File For The Windows Library

#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\glut.h"											// Header File For The OpenGL32 Library
#include "Vector3f.h"
#include "Texture.h"
#include "BoundingBox.h"
#include "Potion.h"
#include "Invisibility.h"
#include "HeightMapTerrain.h"

class PickUpHandler{

public:
	PickUpHandler();
	~PickUpHandler();
	void Initialise(HeightMapTerrain* heightmap);
	void Update(float dt);
	void Render(float dt);

	vector<Potion*> Potions();
	vector<Invisibility*> Invises();


private:
	HeightMapTerrain* hm;
	vector<Invisibility*> v_invis;
	vector<Potion*> v_potion;
	CTexture manaTexture;	// texture for the mesh
	CTexture healthTexture;	// texture for the mesh
	CTexture invisTexture;	// texture for the mesh
	float rotation;
};