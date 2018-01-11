#pragma once
#include <SDL_image.h>
#include <iostream>

#include "GameEntity.h"
#include "const.h"

class Player : public GameEntity
{
public:
	Player(SDL_Renderer* renderer, std::string path);
	~Player();

	void Render();

	//Player movement
	void moveLeft();
	void moveRight();

	//Getter functions
	SDL_Rect* getMainCollider() { return &mainColliderRect; }
	SDL_Rect* getLeftCollider() { return &leftColliderRect; }
	SDL_Rect* getRightCollider() { return &rightColliderRect; }

private:
	SDL_Texture* texture;
	SDL_Rect renderRect;
	SDL_Rect mainColliderRect;
	SDL_Rect leftColliderRect;
	SDL_Rect rightColliderRect;
};

