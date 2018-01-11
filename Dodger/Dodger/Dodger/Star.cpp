#include "Star.h"

Star::Star(SDL_Renderer* renderer, int w, int h, float speed) : MovingGameEntity(renderer)
{
	x = rand() % SCREEN_WIDTH;
	y = 0;
	moveSpeed = speed;

	Box.x = x;
	Box.y = y;
	Box.w = w;
	Box.h = h;
}

Star::~Star()
{
}

void Star::Update()
{
	Box.y += moveSpeed;
}

void Star::Render()
{
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderFillRect(renderer, &Box);
}
