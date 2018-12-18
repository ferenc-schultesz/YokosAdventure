#pragma once
#include <windows.h>									// Header File For The Windows Library
#include ".\include\gl.h"											// Header File For The OpenGL32 Library
#include ".\include\fmod.hpp"
#include ".\include\fmod_errors.h"									// Header File For The Glaux Library


enum Sound
{
	FIREBALL, AMBIENT, NOVA, SWORD, ROLL, CHASING, ATT1,
	ATT2, TAKEDAM, BEXPL, SEXPL, POTION, INVIS
};

class AudioHandler
{
public:
	AudioHandler();
	~AudioHandler();
	bool Initialise();
	bool LoadEventSound(char *filename, FMOD::Sound * sound);
	bool PlayEventSound(Sound s);
	bool LoadMusicStream(char *filename, FMOD::Sound * music);
	bool PlayMusicStream();
	void Update();

private:
		

	void FmodErrorCheck(FMOD_RESULT result);


	FMOD_RESULT result;
	FMOD::System* m_FmodSystem;	// the global variable for talking to FMOD

	FMOD::Sound *s_fireball;
	FMOD::Sound *s_nova;
	FMOD::Sound *s_sword;
	FMOD::Sound *s_roll;
	FMOD::Sound *s_chase;
	FMOD::Sound *s_att1;
	FMOD::Sound *s_att2;
	FMOD::Sound *s_takedam;
	FMOD::Sound *s_bexpl;
	FMOD::Sound *s_sexpl;
	FMOD::Sound *s_potion;
	FMOD::Sound *s_invis;
	
	FMOD::Sound *m_ambient;
	FMOD::Channel* m_musicChannel;

};
