#pragma once

#include <windows.h>
#include "Md2Animation.h"
#include "Vector3f.h"
#include "Camera.h"	
#define _USE_MATH_DEFINES 
#include <math.h> 
#include "include/glew.h" 
#include "include/gl.h" 
#include "CrossFade.h"
#include "Enemy.h"
#include "BoundingBox.h"
#include "AlphaSphere.h"
#include "AudioHandler.h"
#include "SmokeParticleEmitter.h"
#include "Fireball.h"

#define YOHKO_RUN 1 
#define YOHKO_ATTACK 2
#define YOHKO_WALK 11
#define YOHKO_JUMP 4
#define YOHKO_GET_HIT 3


class CPlayer {

public:
	CPlayer();
	~CPlayer();
	void Initialise(Camera* camera, AudioHandler* aud);// CVector3f camVP);			// init player at camera view point
	void Update(double dt);
	void Render();

	void Target(vector<Enemy*> enemy);

	float Mana();
	float Health();

	void Mana(float f);
	void Health(float f);

	float MaxHealth();
	float MaxMana();


	void TakeHit(float hp);
	void Die();
	void Burn();
	void Invis();
	bool GetInvis();

	CBoundingBox GetBBox();
	CMD2Model* GetModel();
	CVector3f Position();
	Enemy* CurrentTarget();
	Fireball* GetFireball();
	CAlphaSphere* GetNova();

	bool GetBurn();
	float GetBurnDebuff();

	float GetInvisBuff();


private:


	Fireball* fireball;
	AudioHandler * m_audio;
	CVector3f m_position;			// player position
	CVector3f m_strafeVector;		// player strafe vector
	CVector3f m_direction;			// player direction
	CMD2Model md2Model;				// MD2 model for player


	float m_speed;					// player speed
	float burnDebuff;
	float invisBuff;

	bool burn;
	bool invis;

	CCrossFade crossfade;

	Enemy* currentTarget;

	CAlphaSphere nova;

	float health;
	float mana;

	float maxMana;
	float maxHealth;

	float meleeDam;
	CVector3f m_prePos;

	vector<Fireball*> fireballs;
	CBoundingBox m_bbox;
	Camera* m_camera;

	void Attack(float dt);
	void Move();

	vector<CSmokeParticleEmitter*> smokes;
};