#pragma once
#include <windows.h> 
#include "Vector3f.h" 
#include "Camera.h" 
#include "./include/glut.h"
#include "SpriteExplosion.h"
#include "BoundingBox.h"
#include "SmokeParticleEmitter.h"
#include "Enemy.h"

class Fireball {
public:
	Fireball(); 
	~Fireball(); 
	void Initialise(); 
	void Update(float dt); 
	void Render(Camera * cam); 
	void Fire(CVector3f direction, CVector3f pos, Enemy* target);
	CSpriteExplosion* GetExplosion();
	CBoundingBox* GetBBox();
	CVector3f GetPosition();
	void Destroy();
	bool Active();

	float Mana();
	float Damage();


private: 
	Enemy* m_target;
	CVector3f m_position; 
	CVector3f m_velocity;
	bool active;
	CSpriteExplosion m_explosion;
	CBoundingBox m_bbox;

	float mana;
	float damage;

	CSmokeParticleEmitter smoke;

	CVector3f originalPos;
};