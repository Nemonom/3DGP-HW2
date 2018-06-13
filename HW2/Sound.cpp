#include "stdafx.h"
#include "Sound.h"


Fmod_snd::Fmod_snd()
{
	FMOD::System_Create(&pSystem);
	pSystem->init(
		1
		, FMOD_INIT_NORMAL
		, nullptr
	);

	pSound = nullptr;

	Add_sound();
}


Fmod_snd::~Fmod_snd()
{	
	pSound->release();
	pSystem->release();
	pSystem->close();
}


void Fmod_snd::Add_sound()
{
	pSystem->createSound(
		"player3.wav"
		, FMOD_DEFAULT | FMOD_LOOP_OFF
		, nullptr
		, &pSound
	);
}

void Fmod_snd::Play_effect()
{
	pSystem->update();
	pSystem->playSound(pSound
		, nullptr, false, nullptr);

}