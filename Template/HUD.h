#pragma once
#include <windows.h>									// Header File For The Windows Library

#include "Player.h"
#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include "Texture.h"
#include "Vector3f.h"
#include <vector>
#include "Text.h"
#include "Gamewindow.h"
#include <sstream>
#include <iomanip>


class HUD
{
public:
	HUD();
	~HUD();
	void Initialise(CPlayer * player, GameWindow* gw);
	void Render();
private:

	void SetOrthographicProjection();
	void RestorePerspectiveProjection();
	GLint m_viewport[4];
	CText m_text;
	bool m_isActive;
	float m_elapsedTime;
	float m_totalTime;
	float m_alpha;
	CPlayer * m_player;
	CTexture playerTexture;	// texture for the mesh
	CTexture frozenTexture;
	CTexture burningTexture;
	CTexture invisTexture;
	float SCREEN_WIDTH, SCREEN_HEIGHT;


	std::string to_string_with_precision(float val);

};