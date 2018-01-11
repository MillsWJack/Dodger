#pragma once

#include "GameEntity.h"
#include "const.h"

#include <time.h>
#include <stdlib.h>

class MovingGameEntity : public GameEntity
{
public:
	MovingGameEntity(SDL_Renderer* renderer);
	~MovingGameEntity();

	SDL_Rect Box;

	float moveSpeed;

private:
	
};

