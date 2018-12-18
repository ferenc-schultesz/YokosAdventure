#include "Potion.h"
#include <cstring>

Potion::Potion() {}



Potion::Potion(CVector3f pos, string type, HeightMapTerrain* heightmap)
{
	hm = heightmap;
	position = pos;
	position.y = hm->ReturnGroundHeight(pos) + 1.2f; // 'y' is adjusted so the mesh is rendered on the ground
	active = true;
	this->type = type;
	
	m_bbox.SetSize(0.45f, 0.7f, 0.45f);
	m_bbox.SetBottom(CVector3f(position.x, position.y-0.55f, position.z));

	mana = 20.0f;
	health = 20.0f;
}

Potion::~Potion()
{

}

void Potion::Create()
{
}

void Potion::Render(float dt, CTexture* texture)
{
	// Vertices
	// GLfloat for Draw
	GLfloat A[3] = { -0.7f, 1.1f, 0.0f };
	GLfloat B[3] = { 0.0f, 1.1f, -0.7f };
	GLfloat C[3] = { 0.0f, 1.1f, 0.7f };
	GLfloat D[3] = { 0.7f, 1.1f, 0.0f };

	GLfloat E[3] = { 0.0f,0.0f,0.0f };

	GLfloat F[3] = { -2.0f, -3.5f, 0.0f };
	GLfloat G[3] = { 0.0f, -3.5f, -2.0f };
	GLfloat H[3] = { 0.0f, -3.5f, 2.0f };
	GLfloat I[3] = { 2.0f, -3.5f, 0.0f };

	// CVector for normals
	CVector3f vA  ( -0.7f, 1.1f, 0.0f );
	CVector3f vB ( 0.0f, 1.1f, -0.7f );
	CVector3f vC  ( 0.0f, 1.1f, 0.7f );
	CVector3f vD  ( 0.7f, 1.1f, 0.0f );

	CVector3f vE  ( 0.0f,0.0f,0.0f );

	CVector3f vF  ( -2.0f, -3.5f, 0.0f );
	CVector3f vG  ( 0.0f, -3.5f, -2.0f );
	CVector3f vH  ( 0.0f, -3.5f, 2.0f );
	CVector3f vI  ( 2.0f, -3.5f, 0.0f );

	// Normals

	// TOP PART
	CVector3f nEDC = ((vC - vE)%(vC - vD));
	GLfloat normalEDC[3] = { nEDC.x,nEDC.y,nEDC.z };
	CVector3f nEBD = ((vD - vE) % (vD - vB));
	GLfloat normalEBD[3] = { nEBD.x,nEBD.y,nEBD.z };
	CVector3f nEAB = ((vB - vE) % (vB - vA));
	GLfloat normalEAB[3] = { nEAB.x,nEAB.y,nEAB.z };
	CVector3f nECA = ((vA - vE) % (vA - vC));
	GLfloat normalECA[3] = { nECA.x,nECA.y,nECA.z };

	// BOTTOM PART
	CVector3f nHIE = ((vE - vH) % (vE - vI));
	GLfloat normalHIE[3] = { nHIE.x,nHIE.y,nHIE.z };
	CVector3f nIGE = ((vE - vI) % (vE - vG));
	GLfloat normalIGE[3] = { nIGE.x,nIGE.y,nIGE.z };
	CVector3f nGFE = ((vE - vG) % (vE - vF));
	GLfloat normalGFE[3] = { nGFE.x,nGFE.y,nGFE.z };
	CVector3f nFHE = ((vE - vF) % (vE - vH));
	GLfloat normalFHE[3] = { nFHE.x,nFHE.y,nFHE.z };
	// TOP AND BOTTOM SURFACE 
	GLfloat topnormal[3] = { 0.0f, 1.0f, 0.0f };
	GLfloat bottomnormal[3] = { 0.0f, -1.0f, 0.0f };

	// Draw object
	glEnable(GL_TEXTURE_2D); 
	glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
	glBegin(GL_TRIANGLES);
	// Top surface
		// ACB
		glNormal3fv(topnormal), glTexCoord2f(0.0f,0.25f), glVertex3fv(A),
		glNormal3fv(topnormal),glTexCoord2f(0.0f, 0.0f), glVertex3fv(C),
		glNormal3fv(topnormal), glTexCoord2f(0.125f, 0.25f), glVertex3fv(B),
		// BCD
		glNormal3fv(topnormal), glTexCoord2f(0.125f, 0.25f), glVertex3fv(B), 
		glNormal3fv(topnormal), glTexCoord2f(0.0f, 0.0f), glVertex3fv(C),
		glNormal3fv(topnormal), glTexCoord2f(0.125f, 0.0f), glVertex3fv(D),

	// Top part
		// EDC
		glNormal3fv(normalEDC), glTexCoord2f(0.25f, 0.0f), glVertex3fv(E),
		glNormal3fv(normalEDC), glTexCoord2f(0.5f, 1.0f), glVertex3fv(D),
		glNormal3fv(normalEDC), glTexCoord2f(0.0f, 1.0f), glVertex3fv(C),
		// EBD
		glNormal3fv(normalEBD),	glTexCoord2f(0.25f, 0.0f), glVertex3fv(E),
		glNormal3fv(normalEBD), glTexCoord2f(0.5f, 1.0f), glVertex3fv(B), 
		glNormal3fv(normalEBD), glTexCoord2f(0.0f, 1.0f), glVertex3fv(D),
		// EAB
		glNormal3fv(normalEAB),	glTexCoord2f(0.25f, 0.0f), glVertex3fv(E), 
		glNormal3fv(normalEAB), glTexCoord2f(0.5f, 1.0f), glVertex3fv(A),
		glNormal3fv(normalEAB), glTexCoord2f(0.0f, 1.0f), glVertex3fv(B),
		// ECA
		glNormal3fv(normalECA), glTexCoord2f(0.25f, 0.0f), glVertex3fv(E), 
		glNormal3fv(normalECA), glTexCoord2f(0.5f, 1.0f), glVertex3fv(C), 
		glNormal3fv(normalECA), glTexCoord2f(0.0f, 1.0f), glVertex3fv(A),
	// Bottom part
		glNormal3fv(normalHIE), glTexCoord2f(0.5f, 0.0f), glVertex3fv(H),
		glNormal3fv(normalHIE), glTexCoord2f(1.0f, 0.0f), glVertex3fv(I),
		glNormal3fv(normalHIE), glTexCoord2f(0.75f, 1.0f), glVertex3fv(E),

		glNormal3fv(normalIGE), glTexCoord2f(0.5f, 0.0f), glVertex3fv(I),
		glNormal3fv(normalIGE), glTexCoord2f(1.0f, 0.0f), glVertex3fv(G),
		glNormal3fv(normalIGE), glTexCoord2f(0.75f, 1.0f), glVertex3fv(E),

		glNormal3fv(normalGFE), glTexCoord2f(0.5f, 0.0f), glVertex3fv(G),
		glNormal3fv(normalGFE), glTexCoord2f(1.0f, 0.0f), glVertex3fv(F),
		glNormal3fv(normalGFE), glTexCoord2f(0.75f, 1.0f), glVertex3fv(E),

		glNormal3fv(normalFHE), glTexCoord2f(0.5f, 0.0f), glVertex3fv(F),
		glNormal3fv(normalFHE), glTexCoord2f(1.0f, 0.0f), glVertex3fv(H),
		glNormal3fv(normalFHE), glTexCoord2f(0.75f, 1.0f), glVertex3fv(E),
	// Bottom surface
		// HFG
		glNormal3fv(bottomnormal), glTexCoord2f(0.375f, 0.0f), glVertex3fv(H),
		glNormal3fv(bottomnormal), glTexCoord2f(0.5f, 0.0f), glVertex3fv(F),
		glNormal3fv(bottomnormal), glTexCoord2f(0.5f, 0.25f), glVertex3fv(G),
		//IHG
		glNormal3fv(bottomnormal), glTexCoord2f(0.375f, 0.25f), glVertex3fv(I),
		glNormal3fv(bottomnormal), glTexCoord2f(0.375f, 0.0f), glVertex3fv(H),
		glNormal3fv(bottomnormal), glTexCoord2f(0.5f, 0.25f), glVertex3fv(G);
	glEnd();


}

CVector3f Potion::GetPosition()
{
	return position;
}

string Potion::GetType() { return type; }
bool Potion::Active() { return active; }

float Potion::Mana()
{
	return mana;
}

float Potion::Health()
{
	return health;
}

CBoundingBox * Potion::BBox()
{
	return &m_bbox;
}


void Potion::Destroy()
{
	active = false;
}
