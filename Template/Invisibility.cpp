#include "Invisibility.h"
#include <cstring>

Invisibility::Invisibility() {}

Invisibility::Invisibility(CVector3f pos, HeightMapTerrain* heightmap)
{
	hm = heightmap;
	position = pos;
	position.y = hm->ReturnGroundHeight(pos) + 2.0f; // 'y' is adjusted so the mesh is rendered on the ground
	active = true;
	texture.Load("Resources\\Textures\\pickups\\invisibility.jpg", false);
	m_textureID = texture.m_textureID;

	m_bbox.SetSize(0.5f, 1.0f, 0.5f);
	m_bbox.SetBottom(CVector3f(position.x, position.y - 0.55f, position.z));
}

Invisibility::~Invisibility()
{

}

void Invisibility::Create()
{
}

void Invisibility::Render(float dt, CTexture* texture)
{

	// Vertices
	// GLfloat for Draw
	GLfloat A[3] = { -1.5f,0.0f,0.0f };
	GLfloat B[3] = { 0.0f, 0.0f, -1.5f };
	GLfloat C[3] = { 0.0f, 0.0f, 1.5f };
	GLfloat D[3] = { 1.5f, 0.0f,0.0f };

	GLfloat J[3] = { 0.0f,2.0f,0.0f };
	GLfloat E[3] = { 0.0f,-2.0f,0.0f };

	// CVector3f for normals
	CVector3f vA  ( -1.5f,0.0f,0.0f );
	CVector3f vB  ( 0.0f, 0.0f, -1.5f );
	CVector3f vC  ( 0.0f, 0.0f, 1.5f );
	CVector3f vD  ( 1.5f, 0.0f,0.0f );

	CVector3f vJ  ( 0.0f,2.0f,0.0f );
	CVector3f vE  ( 0.0f,-2.0f,0.0f );

	// Normals
	// Top
	CVector3f nCDJ = ((vJ - vC) % (vJ - vD));
	GLfloat normalCDJ[3] = { nCDJ.x, nCDJ.y, nCDJ.z };

	CVector3f nDBJ = ((vJ - vD) % (vJ - vB));
	GLfloat normalDBJ[3] = { nDBJ.x, nDBJ.y, nDBJ.z };

	CVector3f nBAJ = ((vJ - vB) % (vJ - vA));
	GLfloat normalBAJ[3] = { nBAJ.x, nBAJ.y, nBAJ.z };

	CVector3f nACJ = ((vJ - vA) % (vJ - vC));
	GLfloat normalACJ[3] = { nACJ.x, nACJ.y, nACJ.z };

	// Bottom
	CVector3f nEDC = ((vC - vE) % (vC - vD));
	GLfloat normalEDC[3] = { nEDC.x, nEDC.y, nEDC.z };

	CVector3f nEBD = ((vD - vE) % (vD - vB));
	GLfloat normalEBD[3] = { nEBD.x, nEBD.y, nEBD.z };

	CVector3f nEAB = ((vB - vE) % (vB - vA));
	GLfloat normalEAB[3] = { nEAB.x, nEAB.y, nEAB.z };

	CVector3f nECA = ((vA - vE) % (vA - vC));
	GLfloat normalECA[3] = { nECA.x, nECA.y, nECA.z };


	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
	/*glEnable(GL_BLEND); 
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);*/
	glBegin(GL_TRIANGLES);
	
	//Top pyramid
		glNormal3fv(normalCDJ), glTexCoord2f(0.0f,0.0f), glVertex3fv(C), 
			glNormal3fv(normalCDJ), glTexCoord2f(1.0f,1.0f), glVertex3fv(D),
			glNormal3fv(normalCDJ), glTexCoord2f(0.5f,1.0f), glVertex3fv(J),

			glNormal3fv(normalDBJ), glTexCoord2f(0.0f, 0.0f), glVertex3fv(D),
			glNormal3fv(normalDBJ), glTexCoord2f(1.0f, 1.0f), glVertex3fv(B),
			glNormal3fv(normalDBJ), glTexCoord2f(0.5f, 1.0f), glVertex3fv(J),

			glNormal3fv(normalBAJ), glTexCoord2f(0.0f, 0.0f), glVertex3fv(B),
			glNormal3fv(normalBAJ), glTexCoord2f(1.0f, 1.0f), glVertex3fv(A),
			glNormal3fv(normalBAJ), glTexCoord2f(0.5f, 1.0f), glVertex3fv(J),

			glNormal3fv(normalACJ), glTexCoord2f(0.0f, 0.0f), glVertex3fv(A),
			glNormal3fv(normalACJ), glTexCoord2f(1.0f, 1.0f), glVertex3fv(C),
			glNormal3fv(normalACJ), glTexCoord2f(0.5f, 1.0f), glVertex3fv(J),

	// Bottom pyramid
			glNormal3fv(normalEDC), glTexCoord2f(0.5f, 1.0f), glVertex3fv(E),
			glNormal3fv(normalEDC), glTexCoord2f(0.0f, 0.0f), glVertex3fv(D),
			glNormal3fv(normalEDC), glTexCoord2f(1.0f, 0.0f), glVertex3fv(C),

			glNormal3fv(normalEBD), glTexCoord2f(0.5f, 1.0f), glVertex3fv(E),
			glNormal3fv(normalEBD), glTexCoord2f(0.0f, 0.0f), glVertex3fv(B),
			glNormal3fv(normalEBD), glTexCoord2f(1.0f, 0.0f), glVertex3fv(D),

			glNormal3fv(normalEAB), glTexCoord2f(0.5f, 1.0f), glVertex3fv(E),
			glNormal3fv(normalEAB), glTexCoord2f(0.0f, 0.0f), glVertex3fv(A),
			glNormal3fv(normalEAB), glTexCoord2f(1.0f, 0.0f), glVertex3fv(B),

			glNormal3fv(normalECA), glTexCoord2f(0.5f, 1.0f), glVertex3fv(E),
			glNormal3fv(normalECA), glTexCoord2f(0.0f, 0.0f), glVertex3fv(C),
			glNormal3fv(normalECA), glTexCoord2f(1.0f, 0.0f), glVertex3fv(A);
		
	glEnd();
	glDisable(GL_BLEND);
}

CVector3f Invisibility::GetPosition()
{
	return position;
}

bool Invisibility::Active() { return active; }

CBoundingBox * Invisibility::BBox()
{
	return &m_bbox;
}


void Invisibility::Destroy()
{
	active = false;
}