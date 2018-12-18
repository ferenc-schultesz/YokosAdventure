#include "Grass.h"
#include <cstring>

Grass::Grass() {}

Grass::Grass(CVector3f pos)
{
	type = 0 + (rand() % static_cast<int>(1 - 0 + 1));
	position = pos;
	rot = 0 + (rand() % static_cast<int>(360 - 0 + 1));
}

Grass::~Grass()
{

}

void Grass::Create()
{
}

void Grass::Render(CTexture* texture)
{

	// Vertices
	// GLfloat for Draw
	GLfloat A[3] = { -1.5f,0.0f,0.0f };
	GLfloat B[3] = { 1.5f, 0.0f, 0.0f };
	GLfloat C[3] = { 1.5f, 1.0f, 0.0f };
	GLfloat D[3] = { -1.5f, 1.5f,0.0f };

	
	GLfloat E[3] = { 0.0f, 0.0f,1.0f };
	GLfloat F[3] = { 0.0f, 0.0f, -1.0f };
	GLfloat G[3] = { 0.0f, 1.3f,-1.0f };
	GLfloat H[3] = { 0.0f,1.3f,1.0f };

	// CVector3f for normals
	CVector3f vA ( -1.5f,0.0f,0.0f );
	CVector3f vB ( 1.5f, 0.0f, 0.0f );
	CVector3f vC ( 1.5f, 1.0f, 0.0f );
	CVector3f vD ( -1.5f, 1.5f,0.0f );

	CVector3f vE ( 0.0f, 0.0f,1.5f );
	CVector3f vF ( 0.0f, 0.0f, -1.5f );
	CVector3f vG ( 0.0f, 1.0f,-1.5f );
	CVector3f vH ( 0.0f,1.0f,1.5f );
	

	// Normals

	CVector3f nABCD = ((vC - vA) % (vC - vB));
	GLfloat normalABCD[3] = { nABCD.x, nABCD.y, nABCD.z };

	CVector3f nEFGH = ((vG - vE) % (vG - vF));
	GLfloat normalEFGH[3] = { nEFGH.x, nEFGH.y, nEFGH.z };

	
	
	glPushMatrix();
		glTranslatef(position.x, position.y, position.z);
		glRotatef(rot, 0, 1, 0);
		glDisable(GL_CULL_FACE);
		glCullFace(GL_FRONT_AND_BACK);
		glEnable(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, texture->m_textureID);
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glAlphaFunc(GL_GREATER, 0.1f);
		glEnable(GL_ALPHA_TEST);
		glBegin(GL_QUADS);
		
			glNormal3fv(normalABCD), glTexCoord2f(0.0f, 0.0f), glVertex3fv(A),
			glNormal3fv(normalABCD), glTexCoord2f(1.0f, 0.0f), glVertex3fv(B),
			glNormal3fv(normalABCD), glTexCoord2f(1.0f, 1.0f), glVertex3fv(C),
			glNormal3fv(normalABCD), glTexCoord2f(0.0f, 1.0f), glVertex3fv(D),
			glNormal3fv(normalEFGH), glTexCoord2f(0.0f, 0.0f), glVertex3fv(E),
			glNormal3fv(normalEFGH), glTexCoord2f(1.0f, 0.0f), glVertex3fv(F),
			glNormal3fv(normalEFGH), glTexCoord2f(1.0f, 1.0f), glVertex3fv(G),
			glNormal3fv(normalEFGH), glTexCoord2f(0.0f, 1.0f), glVertex3fv(H);
		
		glEnd();
	glPopMatrix();


	glDisable(GL_BLEND);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE);

}

CVector3f Grass::GetPosition()
{
	return position;
}

int Grass::GetType()
{
	return type;
}