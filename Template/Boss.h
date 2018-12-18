#pragma once

#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library
#include "Vector3f.h"
#include "OpenAssetImporterMesh.h"
#include "Md2Animation.h"
#include "HeightMapTerrain.h"
#include "BoundingBox.h"
#include "FelBall.h"
#include "Player.h"
#include "Camera.h"

#define BOSS_STAND 1 
#define BOSS_ATT 5
#define BOSS_WALK 2
#define BOSS_PAIN 3
#define BOSS_DIE 6
#define BOSS_HIT 4

using namespace std;

// The Boss class is a wrapper for Boss.md2 model, which will be used as the most basic enemy in the game
class Boss : public Enemy {
private:

	void Die();
	FelBall * felball;
	float felballCD;


public:
	Boss();
	Boss(CVector3f pos, HeightMapTerrain* hmap, AudioHandler* aud);
	~Boss();

	void Update(float dt, Camera* cam, bool playerVisible);
	void Render();
	CBoundingBox GetBBox();
	FelBall* GetFelball();

	CMD2Model* GetModel();
	CVector3f GetPosition();
	CVector3f GetrotVector();
	float GetRotation();
	float GetScale();
	float GetHealth();
	void TakeHit(float damage);


	void Shot();

	void AvoidTree(CVector3f treePos);



	void ChangeState(State s);
	State GetState();
	float GetDamage();
	void SetPosition(CVector3f pos);

};
