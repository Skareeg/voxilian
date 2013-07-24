#ifndef H_AUDIO
#define H_AUDIO

#include <fmod.hpp>
#include "..\..\Globals.h"

class CAudio
{
public:
	//Fmod failure result.
	FMOD_RESULT fresult;
	//Fmod's main system.
	FMOD::System* system;
	//If the system has intiailized.
	bool isInit;
	//Constructor.
	CAudio();
	//Initialize the system.
	void Init(int maxchannels);
	//Update the system.
	void Update();
	//Terminate the system.
	void Terminate();
	//Creates a sound to play.
	FMOD::Sound* CreateSound(string file);
	//Play a generic non channel based sound.
	void PlaySound(FMOD::Sound* sound);
	//Play a channel based sound.
	void PlaySound(FMOD::Sound* sound,FMOD::Channel* channel);
};
extern CAudio Audio;

#endif