#pragma once
#include <SDL_image.h>

class GameEntity
{
public:
	GameEntity(SDL_Renderer* renderer);
	~GameEntity();

	float x;
	float y;
	float width;
	float height;

protected:
	SDL_Renderer* renderer;
};

