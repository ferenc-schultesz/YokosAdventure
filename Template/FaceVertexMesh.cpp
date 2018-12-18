#include "FaceVertexMesh.h"
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

FaceVertexMesh::FaceVertexMesh()
{}

FaceVertexMesh::~FaceVertexMesh()
{}

// Compute the normal of a triangle using the cross product
CVector3f FaceVertexMesh::ComputeTriangleNormal(unsigned int tId)
{
	CVertex v0, v1, v2;
	CVector3f normal, p, q;

	v0 = m_vertices[m_triangles[3 * tId]];
	v1 = m_vertices[m_triangles[3 * tId + 1]];
	v2 = m_vertices[m_triangles[3 * tId + 2]];

	p = CVector3f(v1.x, v1.y, v1.z) - CVector3f(v0.x, v0.y, v0.z);
	q = CVector3f(v2.x, v2.y, v2.z) - CVector3f(v0.x, v0.y, v0.z);
	normal = p % q; // Cross product
	normal.Normalise();

	return normal;
}


void FaceVertexMesh::ComputeTextureCoordsXZ(float xScale, float zScale)
{
	// Set texture coords based on the x and z coordinates
	for (unsigned int i = 0; i < m_vertices.size(); i++) {
		m_vertices[i].s = m_vertices[i].x / xScale;
		m_vertices[i].t = m_vertices[i].z / zScale;
	}
}
void FaceVertexMesh::ComputeVertexNormals()
{

	for (unsigned int i = 0; i < m_vertices.size(); i++) {
		CVertex v = m_vertices[i];

		// Get normal for each triangle around v in one ring neighbourhood
		CVector3f normalSum = CVector3f(0, 0, 0);
		int faceCount = 0;
		for (unsigned int j = 0; j < m_onTriangle[i].id.size(); j++) {
			int tId = m_onTriangle[i].id[j];
			normalSum += ComputeTriangleNormal(tId);
			faceCount++;
		}
		normalSum = normalSum / (float)faceCount;
		normalSum.Normalise();

		m_vertices[i].nx = normalSum.x;
		m_vertices[i].ny = normalSum.y;
		m_vertices[i].nz = normalSum.z;

	}
}



bool FaceVertexMesh::CreateFromTriangleList(const std::vector<CVertex> &vertices, const std::vector<unsigned int> &triangles)
{
	// Set the vertices and indices
	m_vertices = vertices;
	m_triangles = triangles;

	// Now we must fill the onTriangle list
	m_onTriangle.resize(m_vertices.size());
	unsigned int numTriangles = (unsigned int)(triangles.size() / 3);
	for (unsigned int t = 0; t < numTriangles; t++) {
		m_onTriangle[m_triangles[t * 3]].id.push_back(t);
		m_onTriangle[m_triangles[t * 3 + 1]].id.push_back(t);
		m_onTriangle[m_triangles[t * 3 + 2]].id.push_back(t);
	}

	// Compute vertex normals and texture coords
	ComputeVertexNormals();
	ComputeTextureCoordsXZ(5.0f, 5.0f);


	return true;
}

void FaceVertexMesh::Render()
{
	// Set material properties for the mesh: diffuse and ambient
	GLfloat mat_ambient4[] = { 0.1f, 0.1f, 0.1f, 1.0f };
	GLfloat mat_diffuse4[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat mat_specular4[] = { 0.0f, 0.0f, 0.0f, 1.0f };
	glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient4);
	glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse4);
	glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular4);

	// Set OpenGL state variables here to make sure the state is correct
	//glEnable(GL_LIGHTING);
	glShadeModel(GL_SMOOTH);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

	/*
	// Render using glBegin... glEnd
	for (unsigned int i = 0; i < m_triangles.size() / 3; i++) {
	CVertex v1 = m_vertices[m_triangles[3*i]];
	CVertex v2 = m_vertices[m_triangles[3*i+1]];
	CVertex v3 = m_vertices[m_triangles[3*i+2]];
	glBegin(GL_TRIANGLES);
	glTexCoord2f(v1.s, v1.t);
	glNormal3f(v1.nx, v1.ny, v1.nz);
	glVertex3f(v1.x, v1.y, v1.z);

	glTexCoord2f(v2.s, v2.t);
	glNormal3f(v2.nx, v2.ny, v2.nz);
	glVertex3f(v2.x, v2.y, v2.z);

	glTexCoord2f(v3.s, v3.t);
	glNormal3f(v3.nx, v3.ny, v3.nz);
	glVertex3f(v3.x, v3.y, v3.z);

	glEnd();

	}
	*/


	// Render using a vertex array


	// Enable vertex position, normal, texture coords
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	glEnableClientState(GL_TEXTURE_COORD_ARRAY);

	// Tell OpenGL where to find the positions, normals, and texture coords in the vertex array
	glVertexPointer(3, GL_FLOAT, sizeof(CVertex), &m_vertices[0].x);
	glNormalPointer(GL_FLOAT, sizeof(CVertex), &m_vertices[0].nx);
	glTexCoordPointer(2, GL_FLOAT, sizeof(CVertex), &m_vertices[0].s);

	// Draw
	glDrawElements(GL_TRIANGLES, m_triangles.size(), GL_UNSIGNED_INT, &m_triangles[0]);

	// Disable 
	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
	glDisableClientState(GL_TEXTURE_COORD_ARRAY);

	//glDisable(GL_LIGHTING);
}
