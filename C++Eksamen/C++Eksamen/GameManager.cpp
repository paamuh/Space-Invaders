#include "GameManager.h"
#include <SDL_ttf.h>
#include <iostream>
#include <chrono>


void GameManager::startGame()
{
	if (gameIsRunning)
		return;

	initalizeSDL();
	initializeComponents();
	gameLoop();
}

void GameManager::exitGame()
{
	gameIsRunning = false;
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	TTF_Quit();
	SDL_Quit();
}



void GameManager::checkForPlayerLaserCollision(Player & player)
{
	std::vector <Laser*> lasers = player.getPlayerLaser();
	std::vector<std::shared_ptr<StandardBot>> _currentBots = botManagerSptr->getCurrentBots();
	
	for (auto &i : _currentBots)
	{
		for (auto &j : lasers) {
			if (SDL_HasIntersection(i->getRect(), j->getRect())) {

				std::cout << "HIT" << std::endl;
				playerSptr->erasePlayerLaser(j);
				botManagerSptr->eraseBot(i);
			}	
		}
	}	
}

void GameManager::checkForPlayerAlienCollision()
{
	std::vector<std::shared_ptr<StandardBot>> _currentBots = botManagerSptr->getCurrentBots();

	for (auto &i : _currentBots)
	{
		if (SDL_HasIntersection(i->getRect(), playerSptr->getRect())) {
			std::cout << "Player and alien collided" << std::endl;
			gameIsLost = true;
			lives = 0;
		}
	}
}

void GameManager::checkForBotLaserCollision(Player & player)
{
	std::vector<Laser*> botLaser = botManagerSptr->getBotLaser();

	for (auto &i : botLaser) {

		if (SDL_HasIntersection(i->getRect(), playerSptr->getRect())) {
			std::cout << "Alien shot player" << std::endl;
			PLAYER_SPACESHIP_PATH = "bmp/spaceHIT.bmp";
			botManagerSptr->eraseBotLaser(i);
			lives--;
			gameIsLost = true;			
		}
	}
}


SDL_Renderer * GameManager::getRenderer()
{
	return renderer;
}

std::shared_ptr<Player> GameManager::getPlayer()
{
	return playerSptr;
}

int GameManager::getWindowHeight() const
{
	return WINDOW_HEIGHT;
}

int GameManager::getWindowWidth() const
{
	return WINDOW_WIDTH;
}

int GameManager::getLives()
{
	return lives;
}

void GameManager::initalizeSDL()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
	{
		std::cout << "WARNING: Linear texture filtering not enabled" << std::endl;
	}

	window = SDL_CreateWindow("SPACE INVADERS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (window == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	int *h;
	int *w;
	h = &WINDOW_HEIGHT;
	w = &WINDOW_WIDTH;
	SDL_GL_GetDrawableSize(window, w, h);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	SDL_SetRenderDrawColor(renderer, 0,0,0,0);
}

void GameManager::initializeComponents()
{
	inputManagerSptr.reset(new InputManager());
	botManagerSptr.reset(new BotManager());
	playerSptr.reset(new Player(500, 700, 40, 100, PLAYER_SPACESHIP_PATH));

	botManagerSptr->initializeStandardBots();
}

void GameManager::gameLoop()
{
	gameIsRunning = true;
	
	int _framesCount = 0;

	while (gameIsRunning)
	{
		botManagerSptr->shoot();

		_frameStart = SDL_GetTicks();
	
		inputManagerSptr->handleInput();

		updateComponents();

		SDL_RenderClear(renderer);

		renderComponents();
		
		gameLostAndDone();
		
		isGameWon();

		playerSptr->displayLives();
		
		SDL_RenderPresent(renderer);

		frameTime = SDL_GetTicks() - _frameStart;

		checkForPlayerLaserCollision(*playerSptr);
		
		checkForPlayerAlienCollision();

		checkForBotLaserCollision(*playerSptr);

		if (_framesCount >= 10)
		{
			_framesCount = 0;
			botManagerSptr->shiftBotAnime();
		}
		_framesCount++;

		if (FRAME_DELAY > frameTime)
		{
			SDL_Delay(FRAME_DELAY - frameTime);
		}
	}
	exitGame();
}

void GameManager::updateComponents()
{
	botManagerSptr->updateBots();
}

void GameManager::renderComponents()
{
	playerSptr->render();
	
	botManagerSptr->renderBots();
	botManagerSptr->renderLaser();
}

void GameManager::isGameWon()
{
	std::vector<std::shared_ptr<StandardBot>> _currentBots = botManagerSptr->getCurrentBots();
	
	if (_currentBots.size() == 0)
	{
		std::cout << "You've won the game." << std::endl;
		youwonC = new Component(300, 300, 200, 500, YOU_WON_PATH);
		youwonC->render();

		gameIsWon = true;
		unsigned long tempSinceEpoch =
			std::chrono::system_clock::now().time_since_epoch() /
			std::chrono::milliseconds(1);
		if (milliseconds_since_epoch == 0)
		{
			milliseconds_since_epoch = tempSinceEpoch;
		}
		if (tempSinceEpoch - milliseconds_since_epoch >= 5000)
		{
			exitGame();
		}
	}
	gameIsWon = false;
}

void GameManager::gameLostAndDone()
{
	if (lives <= 0) {
		gotC = new Component(300, 300, 200, 500, GOT_PATH);
		gotRectC = new Component(300, 500, 200, 500, RECT_PATH);
		gotC->render();
		gotRectC->render();

		unsigned long tempSinceEpoch =
			std::chrono::system_clock::now().time_since_epoch() /
			std::chrono::milliseconds(1);
		if(milliseconds_since_epoch == 0)
		{
			milliseconds_since_epoch = tempSinceEpoch;
		}
		if (tempSinceEpoch - milliseconds_since_epoch >= 5000)
		{
			exitGame();
		}
	}
}

