	#ifndef GAME_MANAGER_H
#define GAME_MANAGER_H

#include "SDL.h"
#undef main
//#include "SDL_image.h"

#include "InputManager.h"
#include "BotManager.h"
#include "Player.h"
#include <memory>
#include <vector>

class GameManager
{
public:
	static GameManager& getInstance()
	{
		static GameManager instance;
		return instance;
	}
	GameManager(GameManager const &) = delete;
	void operator = (GameManager const&) = delete;

	void startGame();
	void exitGame();
	void checkForPlayerLaserCollision(Player & player);
	void checkForPlayerAlienCollision();
	void checkForBotLaserCollision(Player & player);

	SDL_Renderer * getRenderer();
	std::shared_ptr<Player> getPlayer();

	int getWindowHeight() const;
	int getWindowWidth() const;
	int getLives();
	
	

private:
	GameManager() {}

	bool gameIsRunning;

	std::shared_ptr<InputManager> inputManagerSptr;
	std::shared_ptr<BotManager> botManagerSptr;
	

	SDL_Window * window;
	SDL_Texture * texture;
	SDL_Renderer * renderer;
	
	Component* youwonC;
	Component* gotC;
	Component* gotRectC;


	std::shared_ptr<Player> playerSptr;

	void initalizeSDL();
	void initializeComponents();
	void gameLoop();
	void updateComponents();
	void renderComponents();

	void isGameWon();
	void gameLostAndDone();

	bool gameIsWon = false;
	bool gameIsLost = false;
	int frameTime;
	int WINDOW_WIDTH = 1000;
	int WINDOW_HEIGHT = 800;
	int lives = 3;

	const int FPS = 60;
	const int FRAME_DELAY = 1000 / FPS;
	unsigned long milliseconds_since_epoch = 0;
	Uint32 _frameStart;
	
	const char * PLAYER_SPACESHIP_PATH = "bmp/space.bmp";
	const char * YOU_WON_PATH = "bmp/youwonthegame.bmp";
	const char * GOT_PATH = "bmp/GOT.bmp";
	const char * RECT_PATH = "bmp/RECT.bmp";
	
};

#endif // !GAME_MANAGER_H



