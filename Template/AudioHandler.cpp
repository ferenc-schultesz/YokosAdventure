#include "AudioHandler.h"

#pragma comment(lib, "lib/fmodex_vc.lib")

AudioHandler::AudioHandler()
{}

AudioHandler::~AudioHandler()
{}

bool AudioHandler::Initialise()
{
	// Create an FMOD system
	result = FMOD::System_Create(&m_FmodSystem);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	// Initialise the system
	result = m_FmodSystem->init(32, FMOD_INIT_NORMAL, 0);
	FmodErrorCheck(result);
	if (result != FMOD_OK)
	{
		return false;
	}
	else
	{
		// Load all sound effects and music
		result = m_FmodSystem->createSound("Resources\\Audio\\ambient.mp3", FMOD_HARDWARE, 0, &m_ambient);

		result = m_FmodSystem->createSound("Resources\\Audio\\fireball.wav", FMOD_HARDWARE, 0, &s_fireball);
		result = m_FmodSystem->createSound("Resources\\Audio\\nova.mp3", FMOD_HARDWARE, 0, &s_nova);
		result = m_FmodSystem->createSound("Resources\\Audio\\sword.wav", FMOD_HARDWARE, 0, &s_sword);
		result = m_FmodSystem->createSound("Resources\\Audio\\roll.wav", FMOD_HARDWARE, 0, &s_roll);
		result = m_FmodSystem->createSound("Resources\\Audio\\chase.wav", FMOD_HARDWARE, 0, &s_chase);
		result = m_FmodSystem->createSound("Resources\\Audio\\att1.wav", FMOD_HARDWARE, 0, &s_att1);
		result = m_FmodSystem->createSound("Resources\\Audio\\att2.wav", FMOD_HARDWARE, 0, &s_att2);
		result = m_FmodSystem->createSound("Resources\\Audio\\takeDam.wav", FMOD_HARDWARE, 0, &s_takedam);
		result = m_FmodSystem->createSound("Resources\\Audio\\bExpl.mp3", FMOD_HARDWARE, 0, &s_bexpl);
		result = m_FmodSystem->createSound("Resources\\Audio\\sExpl.wav", FMOD_HARDWARE, 0, &s_sexpl);
		result = m_FmodSystem->createSound("Resources\\Audio\\potion.wav", FMOD_HARDWARE, 0, &s_potion);
		result = m_FmodSystem->createSound("Resources\\Audio\\invis.wav", FMOD_HARDWARE, 0, &s_invis);
		return true;
	}
}

// Load an event sound
bool AudioHandler::LoadEventSound(char *filename, FMOD::Sound * sound)
{
	result = m_FmodSystem->createSound(filename, FMOD_HARDWARE, 0, &sound);
	FmodErrorCheck(result);
	if (result != FMOD_OK) 
		return false;

	return true;
}

// Play an event sound
bool AudioHandler::PlayEventSound(Sound s)
{
	switch (s)
	{
	case FIREBALL:
		//soundToPlay = s_fireball;
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_fireball, false, NULL);
		break;
	case NOVA:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_nova, false, NULL);
		break;
	case SWORD:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_sword, false, NULL);
		break;
	case ROLL:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_roll, false, NULL);
		break;
	case CHASING:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_chase, false, NULL);
		break;
	case ATT1:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_att1, false, NULL);
		break;
	case ATT2:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_att2, false, NULL);
		break;
	case TAKEDAM:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_takedam, false, NULL);
		break;
	case BEXPL:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_bexpl, false, NULL);
		break;
	case SEXPL:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_sexpl, false, NULL);
		break;
	case POTION:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_potion, false, NULL);
		break;
	case INVIS:
		result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, s_invis, false, NULL);
		break;
	}
	if (result != FMOD_OK)
		return false;
	return true;
}


// Load a music stream
bool AudioHandler::LoadMusicStream(char *filename, FMOD::Sound * music)
{
	result = m_FmodSystem->createStream(filename, FMOD_SOFTWARE | FMOD_LOOP_NORMAL, 0, &music);
	FmodErrorCheck(result);

	if (result != FMOD_OK) 
		return false;

	return true;
}

// Play a music stream
bool AudioHandler::PlayMusicStream()
{
	result = m_FmodSystem->playSound(FMOD_CHANNEL_FREE, m_ambient, false, &m_musicChannel);
	FmodErrorCheck(result);

	if (result != FMOD_OK)
		return false;
	return true;
}

// Check for error
void AudioHandler::FmodErrorCheck(FMOD_RESULT result)
{						
	if (result != FMOD_OK) {
		const char *errorString = FMOD_ErrorString(result);
		// MessageBox(NULL, errorString, "FMOD Error", MB_OK);
		// Warning: error message commented out -- if headphones not plugged into computer in lab, error occurs
	}
}

void AudioHandler::Update()
{
	m_FmodSystem->update();
}
