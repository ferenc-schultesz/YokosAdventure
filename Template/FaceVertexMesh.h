#pragma once
#include <windows.h>									// Header File For The Windows Library
#include <vector>
#include "Vector3f.h"
#include "Vertex.h"
#include ".\gl\gl.h"								// Header File For The OpenGL32 Library

typedef struct {
	std::vector<unsigned int> id;	// list of triangle IDs 
} MTriangleList;

class FaceVertexMesh
{
public:
	FaceVertexMesh();
	~FaceVertexMesh();
	void Render();
	bool CreateFromTriangleList(const std::vector<CVertex> &vertices, const std::vector<unsigned int> &triangles);
	void ComputeVertexNormals();
	CVector3f ComputeTriangleNormal(unsigned int tId);
	void ComputeTextureCoordsXZ(float xScale, float zScale);


private:
	std::vector<CVertex> m_vertices;			// A list of vertices
	std::vector<unsigned int> m_triangles;		// Stores vertex IDs -- every three makes a triangle
	std::vector<MTriangleList> m_onTriangle;	// For each vertex, stores a list of triangle IDs saying which triangles the vertex is on

};