#include "Asteroid.h"

Asteroid::Asteroid(SDL_Renderer* renderer) : MovingGameEntity(renderer)
{
	getRandomSprite();

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
			Box.w = newSurface->w;
			Box.h = newSurface->h;
		}
	}
	SDL_FreeSurface(newSurface);

	x = rand() % SCREEN_WIDTH;
	y = 0;
	moveSpeed = 10;

	Box.w = 80;
	Box.h = Box.w;
	Box.x = x;
	Box.y = y - Box.h;
}

Asteroid::~Asteroid()
{
	SDL_DestroyTexture(texture);
}

bool Asteroid::checkCollisions(SDL_Rect* mainCollider, SDL_Rect* leftCollider, SDL_Rect* rightCollider)
{
	if (SDL_HasIntersection(mainCollider, &collisionRect))
	{
		return true;
	}
	if (SDL_HasIntersection(leftCollider, &collisionRect))
	{
		return true;
	}
	if (SDL_HasIntersection(rightCollider, &collisionRect))
	{
		return true;
	}

	return false;
}

void Asteroid::Update()
{
	Box.y += moveSpeed;
}

void Asteroid::Render()
{
	collisionRect.x = Box.x + 20;
	collisionRect.y = Box.y + 20;
	collisionRect.w = Box.w / 2;
	collisionRect.h = Box.h / 2;

	Clip.x = 8;
	Clip.y = 11;
	Clip.w = 32;
	Clip.h = 30;
	SDL_RenderCopy(renderer, texture, &Clip, &Box);

	//Render Collision Box
	//SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	//SDL_RenderDrawRect(renderer, &collisionRect);
}

void Asteroid::getRandomSprite()
{
	int spriteNum = 1 + rand() % 3;
	switch (spriteNum)
	{
	case 1:
		path = "asteroid1.png";
		break;
	case 2:
		path = "asteroid2.png";
		break;
	case 3:
		path = "asteroid3.png";
		break;
	default:
		path = "asteroid1png";
		break;
	}
}