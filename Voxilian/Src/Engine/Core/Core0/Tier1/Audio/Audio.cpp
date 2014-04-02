#include "Audio.h"
#include "..\Log\Log.h"

CAudio::CAudio()
{
	isInit=false;
	fresult=FMOD::System_Create(&system);
	if(fresult!=FMOD_OK)
	{
		Log.Log("ERROR! HIGH FMOD SYSTEM FAILURE!",0);
	}
}

void CAudio::Init(int maxchannels)
{
	fresult=system->init(maxchannels,FMOD_INIT_3D_RIGHTHANDED,0);
	if(fresult!=FMOD_OK)
	{
		Log.Log("MAIN FMOD SYSTEM INIT FAILURE!",0);
		isInit=false;
	}
	else
	{
		Log.Log("Audio system OK.",0);
		isInit=true;
	}
}

void CAudio::Update()
{
	fresult=system->update();
}

void CAudio::Terminate()
{
	fresult=system->release();
}

FMOD::Sound* CAudio::CreateSound(string file)
{
	FMOD::Sound *sn;
	string fn = "Sounds\\" + file;
	fresult=system->createSound(fn.c_str(),FMOD_DEFAULT,0,&sn);
	return sn;
}
void CAudio::PlaySound(FMOD::Sound* sound)
{
	fresult=system->playSound(FMOD_CHANNEL_FREE,sound,false,0);
}
void CAudio::PlaySound(FMOD::Sound* sound,FMOD::Channel* channel)
{
	fresult=system->playSound(FMOD_CHANNEL_FREE,sound,false,&channel);
}
CAudio Audio;