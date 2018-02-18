#include "Game.h"

Game::Game()
{
	window = NULL;
	renderer = NULL;
	music = NULL;
}

bool Game::Init()
{
	srand(time(NULL));
	SDL_Init(SDL_INIT_VIDEO);

	window = SDL_CreateWindow("Dodger", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == NULL)
	{
		std::cout << "Failed to create window.\n";
		return false;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	if (renderer == NULL)
	{
		std::cout << "Failed to create renderer.\n";
		return false;
	}

	//Initialize TTF
	if (TTF_Init() == -1)
	{
		std::cout << "SDL_ttf could not initialize! SDL_ttf Error: " << TTF_GetError() << std::endl;
	}

	//Initialize Mixer
	if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		std::cout << "SDL_mixer could not initialize! SDL_mixer Error: " << Mix_GetError() << std::endl;
	}

	//Initialize PNG
	int initFlags = IMG_INIT_PNG;
	if (!(IMG_Init(initFlags) &initFlags))
	{
		std::cout << "Failed to init IMG.\n";
		return false;
	}

	countedFrames = 0;

	fpsTimer.start();

	return true;
}

void Game::newGame()
{
	delete player;
	delete textTexture;
	player = new Player(renderer, "player.png");
	textTexture = new TextTexture(renderer);

	Mix_VolumeMusic(20);
	music = Mix_LoadMUS("spaceMusic.mp3");
	if (music == NULL)
	{
		std::cout << "Failed to load music.\n";
	}

	if (Mix_PlayingMusic() == 0)
	{
		//Play the music
		Mix_PlayMusic(music, -1);
	}

	asteroidSpawnRate = 25;

	if (currentScore > bestScore)
	{
		bestScore = currentScore;
	}
	currentScore = 0;

	if (!asteroidList.empty())
	{
		asteroidList.erase(asteroidList.begin(), asteroidList.end());
	}
}

void Game::Run()
{
	newGame();

	while (1)
	{
		capTimer.start();
		if (SDL_PollEvent(&e) != 0)
		{
			if (e.type == SDL_QUIT || e.key.keysym.sym == SDLK_ESCAPE)
			{
				break;
			}
		}

		float avgFPS = countedFrames / (fpsTimer.getTicks() / 1000.f);
		if (avgFPS > 2000000)
		{
			avgFPS = 0;
		}

		Update();
		Render();
		++countedFrames;

		int frameTicks = capTimer.getTicks();
		if (frameTicks < SCREEN_TICKS_PER_FRAME)
		{
			SDL_Delay(SCREEN_TICKS_PER_FRAME - frameTicks);
		}
	}

	Clean();
}

void Game::Update()
{
	star = new Star(renderer, 1, 1, 5);
	starList.push_back(star);
	largeStar = new Star(renderer, 5, 5, 7);
	largeStarList.push_back(largeStar);

	handleInput();

	if (nextLevel())
	{
		updateDifficulty();
	}

	if (countedFrames % asteroidSpawnRate == 0)
	{
		asteroid = new Asteroid(renderer);
		asteroidList.push_back(asteroid);
	}

	iterateThroughLists();

	checkScreenCollisions(player);
}

void Game::Render()
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
	SDL_RenderClear(renderer);

	//Render stars
	for (Star* currentStar : starList)
	{
		currentStar->Render();
	}
	for (Star* currentLargeStar : largeStarList)
	{
		currentLargeStar->Render();
	}

	player->Render();

	//Render asteroids
	for (Asteroid* currentAsteroid : asteroidList)
	{
		currentAsteroid->Render();
		//Check asteroid collision
		if (currentAsteroid->checkCollisions(
			player->getMainCollider(), 
			player->getLeftCollider(),
			player->getRightCollider()))
		{
			audio->playSound("AsteroidHit.wav");
			newGame();
			SDL_Delay(1000);
			return;
		}
	}

	//Current Score
	textTexture->DrawText("Score: ", 0, 0, 20);
	textTexture->DrawText(std::to_string(currentScore), 100, 0, 20);

	//Best Score
	textTexture->DrawText("Best: ", 0, 30, 20);
	textTexture->DrawText(std::to_string(bestScore), 100, 30, 20);

	//~~~DEBUG~~~
	//Print List sizes
	//std::cout << "\n\n\n\n\n\n\n\n\n\n";
	//std::cout << "Starlist: " << starList.size() << std::endl;
	//std::cout << "LargeStarlist: " << largeStarList.size() << std::endl;
	//std::cout << "AsteroidList: " << asteroidList.size() << std::endl;

	SDL_RenderPresent(renderer);
}

void Game::checkScreenCollisions(GameEntity* obj)
{
	if (obj->x + obj->width > SCREEN_WIDTH)
	{
		obj->x = SCREEN_WIDTH - obj->width;
	}
	if (obj->x < 0)
	{
		obj->x = 0;
	}
	if (obj->y + obj->height > SCREEN_HEIGHT)
	{
		obj->y = SCREEN_HEIGHT - obj->height;
	}
	if (obj->y < 0)
	{
		obj->y = 0;
	}
}

void Game::handleInput()
{
	const Uint8* currentKeyState = SDL_GetKeyboardState(NULL);
	if (currentKeyState[SDL_SCANCODE_A] || currentKeyState[SDL_SCANCODE_LEFT])
	{
		player->moveLeft();
	}
	if (currentKeyState[SDL_SCANCODE_D] || currentKeyState[SDL_SCANCODE_RIGHT])
	{
		player->moveRight();
	}
}

void Game::incrementScore()
{
	if (currentScore >= bestScore)
	{
		bestScore++;
	}
	currentScore++;
}

void Game::updateDifficulty()
{
	asteroidSpawnRate--;
}

void Game::iterateThroughLists()
{

	//Iterate through star list and update if not off screen
	std::list<Star*>::iterator currentStar;
	for (currentStar = starList.begin(); currentStar != starList.end(); currentStar++)
	{
		//Check if star is off screen
		if ((*currentStar)->Box.y + (*currentStar)->Box.h > SCREEN_HEIGHT)
		{
			delete (*currentStar);
			currentStar++;
			starList.erase(starList.begin());
		}
		(*currentStar)->Update();
	}

	//Iterate through large star list and update if not off screen
	std::list<Star*>::iterator currentLargeStar;
	for (currentLargeStar = largeStarList.begin(); currentLargeStar != largeStarList.end(); currentLargeStar++)
	{
		//Check if star is off screen
		if ((*currentLargeStar)->Box.y + (*currentLargeStar)->Box.h > SCREEN_HEIGHT)
		{
			delete (*currentLargeStar);
			currentLargeStar++;
			largeStarList.erase(largeStarList.begin());
		}
		(*currentLargeStar)->Update();
	}

	//Iterate through asteroid list and update if not off screen
	std::list<Asteroid*>::iterator currentAsteroid;
	for (currentAsteroid = asteroidList.begin(); currentAsteroid != asteroidList.end(); currentAsteroid++)
	{
		//Check if asteroid is off screen
		if ((*currentAsteroid)->Box.y > SCREEN_HEIGHT)
		{
			delete(*currentAsteroid);
			currentAsteroid++;
			asteroidList.erase(asteroidList.begin());
			incrementScore();
		}
		(*currentAsteroid)->Update();
	}
}

bool Game::nextLevel()
{
	if (currentScore % 25 == 0 &&
		currentScore > 0 &&
		countedFrames % 10 == 0)
	{
		return true;
	}

	return false;
}

void Game::Clean()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	renderer = NULL;
	window = NULL;

	Mix_FreeMusic(music);
	music = NULL;

	SDL_Quit();
	IMG_Quit();
	TTF_Quit();
	Mix_Quit();
}