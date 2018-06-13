#pragma once
#include "FMOD\fmod.hpp"
#pragma comment(lib, "fmod64_vc.lib")

using namespace FMOD;

class Fmod_snd 
{
public:
	Fmod_snd();
	~Fmod_snd();
	void Play_effect();

private:
	void Add_sound();
	System * pSystem;
	Sound * pSound;
	Channel * pChannel;

};

