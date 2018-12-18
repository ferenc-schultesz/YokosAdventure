#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\include\gl.h"								// Header File For The OpenGL32 Library
#include "Texture.h"

class Background
{
public:
	Background();
	~Background();
	void Initialise();
	void Render();
	void ChangeTexture();								// used to change the texture on the quad when game is loading first level

private:
	UINT m_introtextureID;								
	UINT m_loadtextureID;								
	CTexture introtexture;								// default intro texture
	CTexture loadtexture;								// loading texture
	bool loading;										// true when level 1 is loading
};