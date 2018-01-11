#include "Player.h"

Player::Player(SDL_Renderer* renderer, std::string path) : GameEntity(renderer)
{
	SDL_Surface* newSurface = IMG_Load(path.c_str());
	if (newSurface == NULL)
	{
		std::cout << "Failed to load surface.\n";
	}
	else
	{
		SDL_SetColorKey(newSurface, SDL_TRUE, SDL_MapRGB(newSurface->format, 69, 69, 69));
		texture = SDL_CreateTextureFromSurface(renderer, newSurface);
		if (texture == NULL)
		{
			std::cout << "Failed to create texture from surface.\n";
		}
		else
		{
			renderRect.h = newSurface->h;
			renderRect.w = newSurface->w;
		}
	}
	SDL_FreeSurface(newSurface);

	x = (SCREEN_WIDTH / 2) - (renderRect.w / 2);
	y = SCREEN_HEIGHT * 0.80;
	width = 100;
	height = 100;
}

Player::~Player()
{
	SDL_DestroyTexture(texture);
}

void Player::Render()
{
	renderRect.x = x;
	renderRect.y = y;
	renderRect.h = height;
	renderRect.w = width;
	SDL_RenderCopy(renderer, texture, NULL, &renderRect);

	mainColliderRect.x = x + 25;
	mainColliderRect.y = y;
	mainColliderRect.h = height;
	mainColliderRect.w = 50;

	leftColliderRect.x = x;
	leftColliderRect.y = y + 50;
	leftColliderRect.h = 40;
	leftColliderRect.w = 25;

	rightColliderRect.x = x + 75;
	rightColliderRect.y = y + 50;
	rightColliderRect.h = 40;
	rightColliderRect.w = 25;

	//Render Colliders
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//SDL_RenderDrawRect(renderer, &leftColliderRect);
	//SDL_RenderDrawRect(renderer, &mainColliderRect);
	//SDL_RenderDrawRect(renderer, &rightColliderRect);
}

void Player::moveLeft()
{
	x -= 10;
}

void Player::moveRight()
{
	x += 10;
}