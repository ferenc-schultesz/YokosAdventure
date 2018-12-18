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
#include "AudioHandler.h"
#include "Text.h"
#include "LightingHandler.h"
#include "Material.h"
#include "Background.h"


class Intro
{
public:
	Intro();
	~Intro();
	void Initialise(GameWindow* m_gw);		// Initialises the games (load assets, etc.)
	void Update(float dt);					// Update the simulation at each time step
	void Render(float dt);					// Render the scene
	void DrawHUD();
	Camera m_Camera;
	AudioHandler m_audio;							// Audio using FMOD
	CText m_text;							// Text for the head's up display
	LightingHandler m_lighting;					// Lighting 
	CMaterial m_material;					// Material
		
	Background background;					// object used to render intro screen
	GameWindow* m_GameWindow;
};