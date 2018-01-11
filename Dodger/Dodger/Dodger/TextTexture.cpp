#include "TextTexture.h"

TextTexture::TextTexture(SDL_Renderer* renderer)
{
	this->renderer = renderer;
}

void TextTexture::DrawText(std::string text, int x, int y, int fontSize)
{
	TTF_Font* font = TTF_OpenFont("JackPixel.ttf", fontSize);

	SDL_Color fg = { 255,255,255 };
	SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), fg);

	SDL_Texture* optimizedSurface = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_Rect sizeRect;
	sizeRect.x = 0;
	sizeRect.y = 0;
	sizeRect.w = surface->w;
	sizeRect.h = surface->h;

	SDL_Rect posRect;
	posRect.x = x;
	posRect.y = y;
	posRect.w = sizeRect.w;
	posRect.h = sizeRect.h;

	SDL_RenderCopy(renderer, optimizedSurface, &sizeRect, &posRect);
	SDL_DestroyTexture(optimizedSurface);
	SDL_FreeSurface(surface);
	TTF_CloseFont(font);
}