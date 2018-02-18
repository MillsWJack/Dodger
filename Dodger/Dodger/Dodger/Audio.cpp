#include "Audio.h"

Audio::Audio()
{
}

Audio::~Audio()
{
}

void Audio::playSound(std::string filePath)
{
	Mix_Chunk* audioChunk = Mix_LoadWAV(filePath.c_str());
	Mix_VolumeChunk(audioChunk, 20);
	Mix_PlayChannel(-1, audioChunk, 0);
}