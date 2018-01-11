#pragma once
#include "MovingGameEntity.h"

class Star : public MovingGameEntity
{
public:
	Star(SDL_Renderer* renderer, int w, int h, float speed);
	~Star();

	void Update();
	void Render();
};

