#pragma once

#define _USE_MATH_DEFINES								// Will allow certain constants (like M_PI) to be availabe from <math.h>

#include <windows.h>									// Header File For the Windows Library
#include <stdio.h>										// Header File For the Standard Input/Output Functions
#include <stdlib.h>										// Header File For the Standard Library
#include <math.h>										// Header File For the Math header file
#include ".\include\glew.h"								// Header File For the GLEW Library
#include ".\include\gl.h"								// Header File For the OpenGL32 Library
#include ".\include\glu.h"								// Header File For the GLu32 Library

#include <cstring>
#include "CollisionHandler.h"
// Includes for game objects
#include "Camera.h"
#include "Gamewindow.h"
#include "HighResolutionTimer.h"
#include "SkyBox.h"
#include "OpenAssetImporterMesh.h"
#include "AudioHandler.h"
#include "Text.h"
#include "LightingHandler.h"
#include "Material.h"
#include "SpecialFX.h"
#include "Player.h"
//#include "StaticMesh.h"
#include "Random.h"						// not used, but can add one to vector<Random> to test it
#include "HeightMapTerrain.h"
#include "Imp.h"
#include "Invisibility.h"
#include "AlphaSphere.h"
#include "HUD.h"
#include "Vegetation.h"
#include "PickUpHandler.h"
#include "Boss.h"
#include "Enemy.h"


// This class initialises, updates and renders level one (Forest)
class Forest
{
public:
	Forest();
	~Forest();
	void Initialise(GameWindow* m_gw);		// Initialises the games (load assets, etc.)
	void Update(float dt);					// Update the simulation at each time step
	void Render(float dt);					// Render the scene
	void DrawHUD();							// Draws HUD 
	Camera* GetCamera();
	CPlayer* GetPlayer();
	vector<Enemy*> GetEnemies();

private:
	Camera m_Camera;						// camera

	HeightMapTerrain m_hterrian;			// height  map terrain 
	CSkybox m_skybox;						// Skybox for background
	GameWindow* m_GameWindow;				// pointer for game window

	CSmokeParticleEmitter smoke;
	CSpecialFX m_fx;

	AudioHandler m_audio;							// Audio using FMOD
	CText m_text;							// Text for the head's up display
	LightingHandler m_lighting;					// Lighting 
	CMaterial m_material;					// Material
	
	CPlayer m_Player;						// player

	//vector<StaticMesh*> StaticMeshes;		// stores all static meshes ( plants, buildings)
	vector<Random*> RandomPickups;			// stores all random pick-ups
	vector<Potion*> Potions;				// stores all potions
	vector<Imp*> Imps;						// stores all Imps
	vector<Invisibility*> Invisibilities;	// stores all invisibility power-ups

	CollisionHandler collisionHandler;

	CAlphaSphere nova;

	HUD hud;

	Vegetation vegetation;
	PickUpHandler pickUpHandler;

	Boss* boss;

	vector<Enemy*> enemies;

	bool bossUp;
	bool bossDead;
	bool gameover;
	COpenAssetImporterMesh bunny;


};
