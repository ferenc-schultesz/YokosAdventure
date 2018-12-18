
#pragma once
#include <windows.h>									// Header File For The Windows Library
#include <vector>
#include "Vector3f.h"
#include "FaceVertexMesh.h"
#include "Texture.h"
#include "include\freeimage\FreeImage.h"
#include ".\gl\gl.h"								// Header File For The OpenGL32 Library

class HeightMapTerrain
{
public:
	HeightMapTerrain();
	~HeightMapTerrain();
	bool Create(string sTerrainFilename, string sTextureFilename, CVector3f origin, float terrainSizeX, float terrainSizeZ, float terrainHeightScale);
	float ReturnGroundHeight(CVector3f p);
	void Render();
	bool GetImageBytes(string sTerrainFilename, BYTE **bDataPointer, unsigned int &width, unsigned int &height);


private:
	int m_width, m_height;
	float *m_heightMap;
	FaceVertexMesh m_mesh;
	float m_terrainSizeX, m_terrainSizeZ;
	CVector3f m_origin;
	CTexture m_texture;
	FIBITMAP* m_pDib;


	CVector3f WorldToImageCoordinates(CVector3f p);
	CVector3f ImageToWorldCoordinates(CVector3f p);
};