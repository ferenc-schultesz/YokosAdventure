#include "CrossFade.h"

CCrossFade::CCrossFade()
{
}


CCrossFade::~CCrossFade()
{
}

void CCrossFade::Activate()
{

	m_isActive = true;
	m_elapsedTime = 0.0f;
	m_totalTime = 0.7f; // run the effect for one second
	m_alpha = 0.2f;
}

// Update the crossface based on elapsed time
void CCrossFade::Update(float dt)
{
	
	if (m_isActive == false)
		return;

	m_elapsedTime += dt;

	// Have the alpha start at 0.5 and go to 0 over time
	m_alpha =  0.5f - 0.5f * m_elapsedTime / (float) m_totalTime;

	if (m_elapsedTime > m_totalTime) 
		m_isActive = false;
}


void CCrossFade::SetOrthographicProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	
	glGetIntegerv(GL_VIEWPORT, m_viewport);
	int w = m_viewport[2];
	int h = m_viewport[3];
		
	gluOrtho2D(0, w, 0, h);
	glMatrixMode(GL_MODELVIEW);
}

void CCrossFade::RestorePerspectiveProjection()
{
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

// Render a full-screen quad with varying transparency
void CCrossFade::Render(float red, float green, float blue)
{

	if (m_isActive == false)
		return;

	// Set the OpenGL state and go to 2D mode
	glPushMatrix();
	glDisable(GL_LIGHTING);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_TEXTURE_2D);
	SetOrthographicProjection();
	glLoadIdentity();


	// Render full screen quad
	float w = (float) m_viewport[2];
	float h = (float) m_viewport[3];
	glColor4f(red, green, blue, m_alpha);
	glBegin(GL_QUADS);
		glVertex3f(0, 0, 0);
		glVertex3f(w, 0, 0);
		glVertex3f(w, h, 0);
		glVertex3f(0, h, 0);
	glEnd();

	 
	// Go back to 3D mode (perspective projection)
	RestorePerspectiveProjection();
	glPopMatrix();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_TEXTURE_2D);
	glDisable(GL_BLEND);

}


bool CCrossFade::Active()
{
	return m_isActive;
}