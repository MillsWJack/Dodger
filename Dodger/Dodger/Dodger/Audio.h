#pragma once
#include <SDL_mixer.h>

#include <string>

class Audio
{
public:
	Audio();
	~Audio();

	void playSound(std::string filePath);
};

