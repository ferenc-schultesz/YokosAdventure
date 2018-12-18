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
#include "Gamewindow.h"
#include "HighResolutionTimer.h"
#include "AudioHandler.h"
#include "Text.h"
#include "Forest.h"										// level 1 class
#include "Intro.h"										// intro level class


class Game {
public:

private:
	Game::Game();
	Game::Game(const Game&);

	GameWindow m_GameWindow;
	HINSTANCE m_hinstance;
	CHighResolutionTimer m_highResolutionTimer;		// A timer for measuring the time between frames
	AudioHandler m_audio;									// Audio using FMOD
	CText m_text;									// Text for the head's up display
	Forest forestlevel;								// first level of the game
	Intro introlevel;								// intro screen of the game
	
	double m_dt;			// time between frames						
	bool cursor;			// bool to check if cursor is visible
	int LEVEL;				// actual level of the game
	float zDelta;			// used to get the change in the scroll position of the mouse --> Zoom

	void Initialise();		// Initialises the games (load assets, etc.)
	void GameLoop();		// The game loop calls the update and render methods of the actual level --> no need update and render in game class

	void Game::operator=(const Game&);

	void writeLog(CVector3f v);		// helper function to log the camera view point to a text file

public:
	~Game();
	static Game& GetInstance();
	WPARAM Execute();
	void SetHinstance(HINSTANCE hinstance);
	LRESULT ProcessEvents(HWND window, UINT message, WPARAM w_param, LPARAM l_param);

};