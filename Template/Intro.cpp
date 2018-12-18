#include "Intro.h"



Intro::Intro()
{

}
Intro::~Intro() {}

void Intro::Initialise(GameWindow* m_gw)
{
	m_GameWindow = m_gw;		// saving the game window pointer

	// sets camera to look at background object (intro screen)
	m_Camera.Set(CVector3f(0.0f, 3.1f, 0.0f), CVector3f(0.0f, 3.1f, 15.0f), CVector3f(0, 1, 0), 5.0f);

	// Create a class for rendering text
	m_text.Create(m_GameWindow->GetHdc(), "Arial", 18);
	// initialise background object (intro screen)
	background.Initialise();
}

void Intro::Update(float dt)
{
	// no update necessary, intro screen is static at the moment
}
void Intro::Render(float dt)
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glLoadIdentity();

	// Calling look will put the viewing matrix onto the modelview matrix stack
	m_Camera.Look();

	// sets up a lighting for intro screen
	glEnable(GL_LIGHTING);
	GLfloat ambientLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat diffuseLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat specularLight0[] = { 1.0f, 1.0f, 1.0f, 1.0f };
	GLfloat positionLight0[] = { 0.0f, 1.0f, 1.0f, 0.0f };
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientLight0);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseLight0);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularLight0);
	glLightfv(GL_LIGHT0, GL_POSITION, positionLight0);

	glEnable(GL_LIGHT0);
	glEnable(GL_NORMALIZE);
	// set material
	m_material.SetDefaultMaterial();

	// renders intro screen
	glPushMatrix();
	glTranslatef(0.0f, 3.0f, 7.0f);
	glRotatef(180.0f, 0, 1, 0);
	background.Render();
	glPopMatrix();

}

void Intro::DrawHUD()
{
	CVector3f vector = m_Camera.GetViewPoint() - m_Camera.GetPosition();
	float rad = atan2(vector.z, vector.x);
	float deg = rad * (180 / 3.14f);

	// debug single value
	char value[32];
	//sprintf_s(value, "%f", (m_Camera.GetViewPoint() - m_Camera.GetPosition()).Length());
	sprintf_s(value, "%i", 4);
	char Label[64] = "DEBUG: ";
	strcat_s(Label, value);

	// debug vector values
	char x[32];
	char y[32];
	char z[32];
	sprintf_s(x, "%f", vector.x);
	sprintf_s(y, "%f", vector.x);
	sprintf_s(z, "%f", vector.x);
	char Labelx[64] = "X: ";
	char Labely[64] = "Y: ";
	char Labelz[64] = "Z: ";
	strcat_s(Labelx, x);
	strcat_s(Labely, y);
	strcat_s(Labelz, z);
	//glDisable(GL_LIGHTING);
	m_text.Render(25, m_GameWindow->SCREEN_HEIGHT - 15, 0, 0, 0, Label);  // Draw some text -- useful for debugging and head's up displays
																		  //m_text.Render(m_GameWindow.SCREEN_WIDTH /2, m_GameWindow.SCREEN_HEIGHT/2, 0, 0, 0, Label);
	m_text.Render(m_GameWindow->SCREEN_WIDTH - 190, 15, 0, 0, 0, "Vector");
	m_text.Render(m_GameWindow->SCREEN_WIDTH - 120, 15, 0, 0, 0, Labelx);
	m_text.Render(m_GameWindow->SCREEN_WIDTH - 120, 35, 0, 0, 0, Labely);
	m_text.Render(m_GameWindow->SCREEN_WIDTH - 120, 55, 0, 0, 0, Labelz);
	//glEnable(GL_LIGHTING);
}
