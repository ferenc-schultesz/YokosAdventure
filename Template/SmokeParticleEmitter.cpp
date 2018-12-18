#pragma once
#include "SmokeParticleEmitter.h"

CSmokeParticleEmitter::CSmokeParticleEmitter()
{
	m_active = false;
	accumulatedTime = 0.0f;
}


CSmokeParticleEmitter::~CSmokeParticleEmitter()
{}

void CSmokeParticleEmitter::LoadTexture(char *filename)
{
	// Load the texture
	m_texture.Load((char *)filename, false); // Loads an image.  Make sure the image is in a 32 bit format (tga) with transparency


}

bool CSmokeParticleEmitter::IsActive()
{
	return m_active;
}

void CSmokeParticleEmitter::Initialise(CVector3f smokeTrailStart, CVector3f smokeTrailDirection, int numTotalParticles, float width, float height, Enemy* enemy)
{
	// We're going to launch a set of particles along a ray that starts at smokeTrailStart and is directed along smokeTrailDirection
	m_start = smokeTrailStart;
	m_direction = smokeTrailDirection;
	m_direction.Normalise();
	m_direction *= 2.0f;

	m_width = width;
	m_height = height;

	m_numTotalParticles = numTotalParticles;
	m_active = true;

	m_enemy = enemy;
}

void CSmokeParticleEmitter::Clear()
{
	m_particles.clear();
	m_active = false;
}

void CSmokeParticleEmitter::Render(CVector3f viewVector, CVector3f upVector)
{
	m_texture.Bind();				// Binds the texture for use

	// Render each particle
	for (unsigned int i = 0; i < m_particles.size(); i++) 
		m_particles[i].Render(viewVector, upVector);
	
	
}

void CSmokeParticleEmitter::UpdateParticles(float dt)
{
	CVector3f direction = m_enemy->GetPosition();
	direction.y += 1.3f;
	direction = direction - m_start;
	m_direction = direction;
	m_direction.Normalise();
	m_direction *= 1.2f;

	//static float accumulatedTime = 0.0f;

	m_numAlive = 0;
	for (unsigned int i = 0; i < m_particles.size(); i++) {
		m_particles[i].Update(dt);

		// Count the number of alive particles
		if (m_particles[i].IsAlive())
			m_numAlive++;

	}

	accumulatedTime += dt;

	// Check if there are no more alive particles -- if so, clear
	if (m_active && m_particles.size() > 0 && m_numAlive == 0) {
		Clear();
		return;
	}

	
	// Add a particle every 10 ms, up to the total number of particles to be added
	if (accumulatedTime > 0.05f && m_particles.size() < (unsigned int) m_numTotalParticles) 
	{
		AddParticle();
		accumulatedTime -= 0.05f;
	}

		


}
		
// Add another particle 
void CSmokeParticleEmitter::AddParticle()
{
	CParticle particle;
	CVector3f p = m_start + (float) m_particles.size() * m_direction;
	particle.Initialise(p, m_width, m_height, CVector3f(0, 0, 0), CVector3f(1, 1, 1), 15);
	m_particles.push_back(particle);

}

