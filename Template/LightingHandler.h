#pragma once

#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library
#include "Player.h"
#include "Enemy.h"
#include "Vector3f.h"

class LightingHandler
{
public:
	LightingHandler();


	void InitConstantLights(CPlayer * player, vector<Enemy*> enemies);

	void Update();

	// constant on lights
	void SetDefaultAmbient();
	void SetPlayerSpot(CVector3f pos);
	void SetMoonLight();

	// set up temp lights
	void SetTargetLight(CVector3f pos);
	void SetFelballLight(CVector3f pos);
	void SetFireballLight(CVector3f pos);
	void UpdateEnemiesVector(vector<Enemy*> enemies);

private:

	CPlayer* m_player;
	vector<Enemy*> m_enemies;

};

