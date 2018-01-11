#pragma once
#include <iostream>

#include "MovingGameEntity.h"

class Asteroid : public MovingGameEntity
{
public:
	Asteroid(SDL_Renderer* renderer);
	~Asteroid();

	bool checkCollisions(SDL_Rect* mainCollider, SDL_Rect* leftCollider, SDL_Rect* rightCollider);
	void Update();
	void Render();
	void getRandomSprite();

private:
	SDL_Texture* texture;
	SDL_Rect collisionRect;
	SDL_Rect Clip;
	std::string path;
};

