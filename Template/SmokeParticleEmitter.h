#pragma once
#include <windows.h>									// Header File For The Windows Library
#include "include/glew.h" 
#include "include/gl.h" 							// Header File For The OpenGL32 Library
#include "Vector3f.h"
#include "Texture.h"
#include "Particle.h"
#include "Enemy.h"

class CSmokeParticleEmitter
{

public:

	CSmokeParticleEmitter();
	~CSmokeParticleEmitter();
	void Initialise(CVector3f smokeTrailStart, CVector3f smokeTrailDirection, int numTotalParticles, float width, float height, Enemy* enemy);
	void UpdateParticles(float dt );
	void Render(CVector3f viewVector, CVector3f upVector);
	void LoadTexture(char *filename);
	bool IsActive();
	void Clear();

private:

	CTexture m_texture;
	std::vector<CParticle> m_particles;
	int m_numAlive;
	CVector3f m_start, m_direction;
	float m_width, m_height;
	int m_numTotalParticles;
	bool m_active;

	void AddParticle();
	Enemy* m_enemy;
	float accumulatedTime;

};