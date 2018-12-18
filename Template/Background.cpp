#include "Background.h"
#include "Texture.h"
#include <vector>

Background::Background()
{}

Background::~Background()
{}

void Background::Initialise()
{
	// Load the textures for loading and default
	introtexture.Load("Resources\\Textures\\intro\\background.png", false);
	m_introtextureID = introtexture.m_textureID;
	loadtexture.Load("Resources\\Textures\\intro\\loading.png", false);
	m_loadtextureID = loadtexture.m_textureID;
	loading = false;
}

void Background::Render()
{
	// Bind the textures, loading when level 1 is loading, or default
	if (!loading)
	{
		glBindTexture(GL_TEXTURE_2D, m_introtextureID);
	}
	else
	{
		glBindTexture(GL_TEXTURE_2D, m_loadtextureID);
	}
	glNormal3f(0.0f, 0.0f, 1.0f);

	// Draw a quad
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, -0.0f); glVertex3f(-4, -3, 0);
	glTexCoord2f(1.0f, -0.0f); glVertex3f(4, -3, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex3f(4, 3, 0);
	glTexCoord2f(0.0f, 1.0f); glVertex3f(-4, 3, 0);
	glEnd();

}

void Background::ChangeTexture()
{
	loading = true;
}