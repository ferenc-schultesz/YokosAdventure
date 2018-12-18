#include "Particle.h"
#include <math.h>
#include <stdio.h>

CParticle::CParticle()
{}

CParticle::~CParticle()
{}

void CParticle::Update(float dt)
{
	// Position moving based on velocity (could implement more interesting physical equations here depending on the desired effect
	m_position += m_velocity*dt;

	// Rotation of image
	m_angle += m_angularVelocity*dt;

	// Life decreasing on each iteration
	m_life -= 0.1f * dt;

	// Size of the quad increasing on each iteration
	m_width += 1.0f  * dt;
	m_height += 1.0f * dt;

}

bool CParticle::IsAlive()
{
	if (m_life > 0)
		return true;
	else
		return false;
}


bool CParticle::Initialise(CVector3f pIn, float widthIn, float heightIn, CVector3f startColour, CVector3f endColour, float transitionSpeed)
{
	// Set the initial position and velocity
	m_position = pIn;

	// Give the particle some random velocity in the xz plane
	float r1 = (rand() / (float) RAND_MAX) * 2 - 1;
	float r2 = (rand() / (float) RAND_MAX) * 2 - 1;
	m_velocity = CVector3f(r1, 0.0f, r2);	
	m_velocity.Normalise();
	m_velocity *= 0.1f; 

	// Set the sprite colour sequence, width, height
	m_width = widthIn;
	m_height = heightIn;

	// Set the sprite image intial rotation angle and rotational velocity
	m_angle = 0;
	m_angularVelocity = 1.0f;

	// Set the particle life
	m_life = .5f;

	m_startColour = startColour;
	m_endColour = endColour;
	m_transitionSpeed = transitionSpeed;


	return true;
}


void CParticle::Render(CVector3f lookAt, CVector3f upVector)
{

	if (m_life <= 0.0f)
		return;

	// Billboarding -- form a quad at p in the plane orthogonal to the lookAt vector
	lookAt.Normalise();
	CVector3f xAxis = lookAt % upVector;
	xAxis.Normalise();
	CVector3f yAxis = upVector;
	yAxis.Normalise();

	// Find the vertex positions of the quad
	CVector3f p1 = m_position - m_width*xAxis - m_height*yAxis;
	CVector3f p2 = m_position + m_width*xAxis - m_height*yAxis;
	CVector3f p3 = m_position + m_width*xAxis + m_height*yAxis;
	CVector3f p4 = m_position - m_width*xAxis + m_height*yAxis;

	glEnable(GL_BLEND);									// Enable Blending
	glDisable(GL_LIGHTING);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_FALSE);


	// Allow faster (m_transitionSpeed > 1) or slower transitions (0 < m_transitionSpeed < 1) between the two colours
	float f = (float) pow(m_life, m_transitionSpeed);

	// Interpolate between the start and end colour
	CVector3f colour = (1-f) * m_endColour + f * m_startColour;
	

	glPushMatrix();
		// Translate to origin, rotate about the lookAt vector, and translate back -- remember rotations are about the origin
		glTranslatef(m_position.x, m_position.y, m_position.z);
		glRotatef(m_angle, lookAt.x, lookAt.y, lookAt.z);
		glTranslatef(-m_position.x, -m_position.y, -m_position.z);

		// Draw a textured quad with the current frame
		glColor4f(colour.x, colour.y, colour.z, m_life);
		glBegin(GL_QUADS);		
			glTexCoord2f(0, 0); 
			glVertex3f(p1.x, p1.y, p1.z);
			glTexCoord2f(1, 0); 
			glVertex3f(p2.x, p2.y, p2.z);
			glTexCoord2f(1, 1); 
			glVertex3f(p3.x, p3.y, p3.z);
			glTexCoord2f(0, 1); 
			glVertex3f(p4.x, p4.y, p4.z);
		glEnd();
	glPopMatrix();
	glDisable(GL_BLEND);
	glDepthMask(GL_TRUE);
	glEnable(GL_LIGHTING);

	

}