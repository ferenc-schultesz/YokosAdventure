#pragma once

#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library
#include "Vector3f.h"
#include "OpenAssetImporterMesh.h"
#include "Md2Animation.h"
#include "HeightMapTerrain.h"
#include "BoundingBox.h"
#include "Camera.h"
#include "FelBall.h"
#include "AudioHandler.h"

enum State { PATROL, CHASE, ATTACK, ENRAGE, FROZEN, DEAD };

class Enemy
{
protected:
	AudioHandler* audio;
	CMD2Model model;		// MD2 model
	CVector3f position;		// initial position of the Imp
	CVector3f rotVector;	// rotation vector
	float rotation;			// degrees for rotation
	CVector3f direction;	// direction (which way the Imp is facing
	float scale;			// scale
	HeightMapTerrain* hm;	// pointer to height map terrain to adjust the 'y' coordinate of the mesh 
	float health;			// Current health
	CBoundingBox m_bbox;	// bounding box for ocllisions
	CVector3f originalPos;	// original spawn position, used to keep the enemies near the same area
	float damage;			// melee damage
	State state;			// current state
	Camera* camera;			// camera pointer
	FelBall * felball;		// felball (only used in Boss
	CTexture unitFrameTexture;	// unit frame of enemy
	float maxHealth;		// max health

	virtual void Die();		// called when enemy dies

public:
	Enemy();
	Enemy(CVector3f pos, HeightMapTerrain* hmap, AudioHandler* aud);
	~Enemy();

	CVector3f playerPos;
	bool targeted;
	bool active;
	float timer;
	float frozen;

	virtual void Update(float dt, Camera* cam, bool playerVisible);
	virtual void Render();
	virtual void AvoidTree(CVector3f treePos);
	virtual void TakeHit(float damage);
	virtual void SetPosition(CVector3f pos);
	virtual void Target();
	virtual void ChangeState(State s);
	void Defrost();

	// Getter methods
	float MaxHealth();
	CTexture GetFrameTexture();
	
	// Getter methods, overidden in child classes
	virtual CBoundingBox GetBBox();
	virtual CMD2Model* GetModel();
	virtual CVector3f GetPosition();
	virtual CVector3f GetrotVector();
	virtual float GetDamage();
	virtual float GetRotation();
	virtual float GetScale();
	virtual float GetHealth();
	virtual State GetState();
	virtual FelBall* GetFelball();
};