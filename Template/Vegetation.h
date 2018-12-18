#pragma once

#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library
#include "Grass.h"
#include <math.h>										// Header File For the Math header file
#include <cstring>
#include "Vector3f.h"
#include "Tree.h"


class Vegetation
{
public:
	Vegetation();
	~Vegetation();
	void Initialise(int numOfGrass, HeightMapTerrain* hm);
	void Update();
	void Render();
	vector<Tree*> GetTrees();

private:
	vector<Grass*> grasses;
	vector<Tree*> trees;

	COpenAssetImporterMesh elm_mesh;
	COpenAssetImporterMesh giant_mesh;
	COpenAssetImporterMesh tree_mesh;
	COpenAssetImporterMesh needle01_mesh;
	COpenAssetImporterMesh walnut_mesh;

	COpenAssetImporterMesh grass1_mesh;
	COpenAssetImporterMesh grass2_mesh;
	CTexture grassTexture1;		// texture for the mesh
	UINT grassTextureID1;			// holds the texture Id
	CTexture grassTexture2;		// texture for the mesh
	UINT grassTextureID2;			// holds the texture Id

	int random;
};