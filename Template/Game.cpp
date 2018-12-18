/*
OpenGL Template for IN3026
City University London, School of Informatics
Source code drawn from a number of sources and examples, including contributions from
- Ben Humphrey (gametutorials.com), Christy Quinn, Sam Kellett, and others

For educational use by Deparment of Computer Science, City University London UK.

This template contains a skybox, simple terrain, camera, lighting, mesh loader, sipmle physics, texturing, audio

Potential ways to modify the code:  Add new geometry types, change the terrain, load new meshes, set up lighting,
add in additional music / sound FX, modify camera control, put in a startup screen, collision detection, etc.

Template version 4.0a 13/09/2017
Dr Greg Slabaugh (gregory.slabaugh.1@city.ac.uk)
*/

#include "Game.h"
#include <iostream>
#include <fstream>
// Constructor.  
Game::Game()
{
	m_dt = 0.0f;
	cursor = false;		// cursor is hidden by default
	LEVEL = 1;			// level where the game starts 1 - intro , 2 = forest
}

// Destructor.  Technically we could delete all resources, but when the game ends the OS will free memory for us.
Game::~Game()
{
}

// Initialise the game by loading assets and setting up the scene.  Note, it's best to make OpenGL calls here since we know the rendering context is available.
// Only initialises the current level
void Game::Initialise()
{
	switch (LEVEL)			// initialise level
	{
	case 1:
		introlevel.Initialise(&m_GameWindow);
		break;
	case 2:
		forestlevel.Initialise(&m_GameWindow);
		break;
	}
}

// Calls update and render methods of the current level
void Game::GameLoop()
{
	m_highResolutionTimer.Start();
	switch (LEVEL)
	{
	case 1:
		introlevel.Update(m_dt);
		introlevel.Render(m_dt);
		break;
	case 2:
		forestlevel.Update(m_dt);
		forestlevel.Render(m_dt);
		break;
	}
	SwapBuffers(m_GameWindow.GetHdc());
	m_dt = m_highResolutionTimer.Elapsed();
}

WPARAM Game::Execute()
{
	m_GameWindow.Init(m_hinstance);

	if (!m_GameWindow.GetHdc()) {
		return 1;
	}

	Initialise();
	m_highResolutionTimer.Start();

	double frame_duration = 1.0 / (double) 30.0;  // 30 FPS

	MSG msg;

	while (1) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			if (msg.message == WM_QUIT) {
				break;
			}
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else {
			GameLoop();
		}
	}
	m_GameWindow.Deinit();
	return(msg.wParam);
}

LRESULT Game::ProcessEvents(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	CVector3f pos = CVector3f(forestlevel.GetPlayer()->Position().x, forestlevel.GetPlayer()->Position().y + 6.0f, forestlevel.GetPlayer()->Position().z);
	LRESULT result = 0;
	switch (message) {
	
	case WM_SIZE:
		if (!m_GameWindow.GetFullScreen()) {
			m_GameWindow.SizeOpenGLScreen(LOWORD(l_param), HIWORD(l_param));

			RECT dimensions;
			GetClientRect(window, &dimensions);
			m_GameWindow.SetDimensions(dimensions);
		}
		break;
	case WM_CHAR:
		switch (w_param) 
		{
			case '0': 
				if (LEVEL == 2)
				{
					forestlevel.GetCamera()->FREE_VIEW = !forestlevel.GetCamera()->FREE_VIEW;	// switch to free view on forest level
				}
				break;
			case '1':
				LEVEL = 1;
				Initialise();														// switch to intro level
				break;
			case '2': 
				LEVEL = 2;
				Initialise();														// switch to forest level
				break;
			case 'i':																// makes cursor visible currently no functionality
				if (cursor)
				{
					ShowCursor(false);
					cursor = false;
				}
				else
				{
					ShowCursor(true);
					cursor = true;

				}
				break;
		}
		break;
	case WM_PAINT:
		PAINTSTRUCT ps;
		BeginPaint(window, &ps);
		EndPaint(window, &ps);
		break;

	case WM_MOUSEWHEEL:
		if (LEVEL == 2)
		{
			zDelta = GET_WHEEL_DELTA_WPARAM(w_param);
			forestlevel.GetCamera()->Zoom(zDelta);							// sends zDelta to camera to zoom
		}
		break;

	case WM_KEYDOWN:
		switch (w_param) {
		case VK_TAB:
			if (LEVEL == 2)
			{
				forestlevel.GetPlayer()->Target(forestlevel.GetEnemies());
			}
			break;
		case VK_ESCAPE:
			PostQuitMessage(0);
			break;
		case VK_SPACE:
			if (LEVEL == 2)
			{
				writeLog(forestlevel.GetCamera()->GetViewPoint());						// logs camera viewpoint to text file on forest level, used for level design
			}
			if (LEVEL == 1)															// starts level one if we are on the intro screen
			{
				LEVEL = 2;
				introlevel.background.ChangeTexture();
				introlevel.Render(m_dt);
				SwapBuffers(m_GameWindow.GetHdc());
				Initialise();
			}
			break;

		case VK_F1:
			//forestlevel.smoke.Initialise(forestlevel.m_Camera.GetPosition(), forestlevel.m_Camera.GetViewPoint() - forestlevel.m_Camera.GetPosition(), 10, 1.5, 1.5, forestlevel.m_Player.currentTarget);
			break;
		}
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;


	default:
		result = DefWindowProc(window, message, w_param, l_param);
		break;
	}
	return result;
}



Game& Game::GetInstance()
{
	static Game instance;
	return instance;
}

void Game::SetHinstance(HINSTANCE hinstance)
{
	m_hinstance = hinstance;
}

LRESULT CALLBACK WinProc(HWND window, UINT message, WPARAM w_param, LPARAM l_param)
{
	return Game::GetInstance().ProcessEvents(window, message, w_param, l_param);
}

int WINAPI WinMain(HINSTANCE hinstance, HINSTANCE, PSTR, int)
{
	Game &game = Game::GetInstance();
	game.SetHinstance(hinstance);
	return game.Execute();
}

// helper fucntion to save camera viewpoint to text file
void Game::writeLog(CVector3f v)
{
	float x = v.x;
	float y = v.y;
	float z = v.z;
	ofstream myfile;
	myfile.open("temp.txt", ios::app);
	myfile << "(" << std::to_string(x) << "f, " << std::to_string(y) << "f, " << std::to_string(z) << "f)\n";

	myfile.close();
}