#pragma once
#include <SDL_ttf.h>

#include <iostream>
#include <string>

class TextTexture
{
public:
	TextTexture(SDL_Renderer* renderer);

	void DrawText(std::string text, int x, int y, int fontSize);

private:
	SDL_Renderer* renderer;
};

