#pragma once

#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library
#include "Vector3f.h"
#include "OpenAssetImporterMesh.h"
#include "Md2Animation.h"
#include "HeightMapTerrain.h"
#include "BoundingBox.h"
#include "Enemy.h"

#define IMP_STAND 0 
#define IMP_ATT 2
#define IMP_WALK 1
#define IMP_PAIN 3
#define IMP_DIE 4
//using namespace std;

//enum State {PATROL, CHASE, ATTACK, ENRAGE, DEAD};

// The Imp class is a wrapper for Imp.md2 model, which will be used as the most basic enemy in the game
class Imp: public Enemy {

private:
	void Die();
	
public:
	Imp();
	Imp(CVector3f pos, HeightMapTerrain* hmap, AudioHandler* aud);
	~Imp();

	void Update(float dt, Camera* cam, bool playerVisible);
	void Render();
	CBoundingBox GetBBox();
	//CVector3f playerPos;
	void AvoidTree(CVector3f treePos);
	CMD2Model* GetModel();
	CVector3f GetPosition();
	CVector3f GetrotVector();
	float GetRotation();
	float GetScale();
	float GetHealth();
	void TakeHit(float damage);



	void ChangeState(State s);
	State GetState();
	float GetDamage();
	void SetPosition(CVector3f pos);
	FelBall* GetFelball();
}; 
