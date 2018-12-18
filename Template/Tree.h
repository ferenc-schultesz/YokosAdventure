#pragma once

#include "include/glew.h" 
#include "include/gl.h" 
#include "Vector3f.h"
#include "OpenAssetImporterMesh.h"
#include "HeightMapTerrain.h"
#include "BoundingBox.h"

using namespace std;

// This class is used to load and render obj or 3ds meshes
class Tree {
private:

	int type;
	CVector3f position;				// position in word coordinates
	CVector3f rotVector;			// rotation vector 

	float scale;					// scale
	HeightMapTerrain* m_pHM;		// pointer to height map terrain to adjust the 'y' coordinate of the mesh
	CBoundingBox m_bbox;

public:
	Tree();
	Tree( CVector3f pos, HeightMapTerrain* hm);
	~Tree();

	void Render(COpenAssetImporterMesh* mesh);

	CBoundingBox GetBBox();
	CVector3f GetPosition();
	CVector3f GetrotVector();
	float GetScale();
	int GetType();

};