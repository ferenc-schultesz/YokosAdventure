#include "Terrain.h"
#include "Texture.h"
#include <vector>

CTerrain::CTerrain()
{}

CTerrain::~CTerrain()
{}

bool CTerrain::Initialise()
{
	// Load the texture
	CTexture texture;
	texture.Load("Resources\\Textures\\Terrain.bmp", false); 
	m_textureID = texture.m_textureID;
	
	return true;
}

void CTerrain::Render()
{

	float TERRAIN_SIZE = 500;
	
	GLfloat x, y, z, length, width;
	length = TERRAIN_SIZE / 2.0f;
	width = TERRAIN_SIZE / 2.0f;
	
	// Centre terrain around 0, 0, 0;
	x = -width  / 2;
	y = 0;
	z = -length / 2;

	// Bind the texture	
	glBindTexture(GL_TEXTURE_2D, m_textureID);

	glNormal3f(0.0f, 1.0f, 0.0f);

	// Draw a quad
	glBegin(GL_QUADS);		
		glTexCoord2f(1.0f, 0.0f); glVertex3f(x,			y,			z);
		glTexCoord2f(1.0f, 1.0f); glVertex3f(x,			y,			z + length);
		glTexCoord2f(0.0f, 1.0f); glVertex3f(x + width, y,			z + length); 
		glTexCoord2f(0.0f, 0.0f); glVertex3f(x + width, y,			z);
	glEnd();



}
