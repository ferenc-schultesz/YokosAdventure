#include "Random.h"
#include <cstring>

Random::Random(){}

Random::Random(CVector3f pos)
{
	position = pos;
	active = true;
	texture.Load("Resources\\Textures\\pickups\\random.png",false);
	textureId = texture.m_textureID;
}

Random::~Random()
{

}

void Random::Create()
{
}

void Random::Render(float dt)
{
	// Vertices
	//GLfloat for Draw
	GLfloat A[3] = { 0,1,0 };
	GLfloat B[3] = { 1,0,0 };
	GLfloat C[3] = { 0,0,1 };
	GLfloat D[3] = { 0,0,0 };
	// CVector for normals
	CVector3f vA ( 0,1,0 );
	CVector3f vB ( 1,0,0 );
	CVector3f vC ( 0,0,1 );
	CVector3f vD ( 0,0,0 );

	// Normals
	CVector3f nCBA = ((vA - vC) % (vA - vB));
	GLfloat normalCBA[3] = { nCBA.x,nCBA.y,nCBA.z };
	CVector3f nBDA = ((vA - vB) % (vA - vD));
	GLfloat normalBDA[3] = { nBDA.x,nBDA.y,nBDA.z };
	CVector3f nCAD = ((vD - vC) % (vD - vA));
	GLfloat normalCAD[3] = { nCAD.x,nCAD.y,nCAD.z };
	CVector3f nDBC = ((vC - vD) % (vC - vB));
	GLfloat normalDBC[3] = { nDBC.x,nDBC.y,nDBC.z };

	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, textureId);
	glBegin(GL_TRIANGLES);
	// side 1
		glNormal3fv(normalCBA), glTexCoord2f(0.5f, 0.0f), glVertex3fv(C),
		glNormal3fv(normalCBA), glTexCoord2f(1.0f, 0.0f), glVertex3fv(B),
		glNormal3fv(normalCBA), glTexCoord2f(0.75f, 1.0f), glVertex3fv(A),
	// side 2
		glNormal3fv(normalBDA), glTexCoord2f(0.5f, 0.0f),glVertex3fv(B),
		glNormal3fv(normalBDA), glTexCoord2f(0.25f, 1.0f), glVertex3fv(D),
		glNormal3fv(normalBDA), glTexCoord2f(0.0f, 0.0f), glVertex3fv(A),
	// side 3
		glNormal3fv(normalCAD), glTexCoord2f(0.75f, 1.0f), glVertex3fv(C),
		glNormal3fv(normalCAD), glTexCoord2f(0.5f, 0.0f), glVertex3fv(A),
		glNormal3fv(normalCAD), glTexCoord2f(1.0f, 0.0f), glVertex3fv(D),
	// side 4
		glNormal3fv(normalDBC), glTexCoord2f(0.0f, 0.0f), glVertex3fv(D),
		glNormal3fv(normalDBC), glTexCoord2f(0.25f, 1.0f), glVertex3fv(B),
		glNormal3fv(normalDBC), glTexCoord2f(0.5f, 0.0f), glVertex3fv(C);
	glEnd();
}


CVector3f Random::GetPosition() { return position; }