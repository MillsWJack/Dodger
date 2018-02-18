#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "Player.h"
#include "Star.h"
#include "Asteroid.h"
#include "Timer.h"
#include "const.h"
#include "TextTexture.h"
#include "Audio.h"

#include <list>
#include <iostream>

class Game
{
public:
	Game();
	
	bool Init();
	void newGame();
	void Run();
	void Update();
	void Render();
	void checkScreenCollisions(GameEntity* obj);
	void handleInput();
	void incrementScore();
	void updateDifficulty();
	void iterateThroughLists();

	bool nextLevel();

	void Clean();

private:
	SDL_Renderer* renderer;
	SDL_Window* window;
	Mix_Music* music;

	SDL_Event e;

	Timer fpsTimer;
	Timer capTimer;

	std::list<Star*> largeStarList;
	std::list<Star*> starList;
	std::list<Asteroid*> asteroidList;

	Asteroid* asteroid;
	Player* player;
	Star* largeStar;
	Star* star;
	Audio* audio;
	TextTexture* textTexture;


	unsigned int currentScore;
	unsigned int bestScore;
	unsigned int countedFrames;
	unsigned int asteroidSpawnRate;

	float avgFPS;
};

