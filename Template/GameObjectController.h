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
// Includes for game objects
#include "Camera.h"
#include "Gamewindow.h"
#include "HighResolutionTimer.h"
#include "Terrain.h"
#include "SkyBox.h"
#include "OpenAssetImporterMesh.h"
#include "Audio.h"
#include "Text.h"
#include "Lighting.h"
#include "Material.h"
#include "Md2Animation.h"
#include "SpecialFX.h"
#include "Player.h"
#include "StaticMesh.h"
#include "Random.h"
#include "Potion.h"
#include "Background.h"
#include "HeightMapTerrain.h"
#include "Imp.h"
#include "Invisibility.h"

class GameObjectController
{
public:
	GameObjectController();
	GameObjectController();
	void Initialize();
	void Update(float dt);
	void Render(float dt);

	CPlayer m_Player;						// player
	Camera m_Camera;						// camera
	HeightMapTerrain m_hterrian;			// height  map terrain 
	CSkybox m_skybox;						// Skybox for background

	vector<StaticMesh*> StaticMeshes;		// stores all static meshes ( plants, buildings)
	vector<Random*> RandomPickups;			// stores all random pick-ups
	vector<Potion*> Potions;				// stores all potions
	vector<Imp*> Imps;						// stores all Imps
	vector<Invisibility*> Invisibilities;	// stores all invisibility power-ups



private:


};