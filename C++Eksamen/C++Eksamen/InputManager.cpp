#include "InputManager.h"
#include "GameManager.h"


InputManager::InputManager()
{
}


InputManager::~InputManager()
{
}

void InputManager::handleInput()
{
	while (SDL_PollEvent(&sdlEvent) != 0)
	{
		if (sdlEvent.type == SDL_QUIT)
		{
			GameManager::getInstance().exitGame();
			return;
		}
	}

	currentKeyStates = (Uint8*)SDL_GetKeyboardState(nullptr);
	int keyCount = sizeof(currentKeyStates) / sizeof(*currentKeyStates);

	if (currentKeyStates[SDL_SCANCODE_ESCAPE])
	{
		GameManager::getInstance().exitGame();
		return;
	}
	else if (currentKeyStates[SDL_SCANCODE_SPACE] && currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		GameManager::getInstance().getPlayer()->shoot();
		GameManager::getInstance().getPlayer()->moveRight(4);
	}
	else if (currentKeyStates[SDL_SCANCODE_SPACE] && currentKeyStates[SDL_SCANCODE_LEFT])
	{
		GameManager::getInstance().getPlayer()->shoot();
		GameManager::getInstance().getPlayer()->moveLeft(4);
	}
	else if (currentKeyStates[SDL_SCANCODE_SPACE])
	{
		GameManager::getInstance().getPlayer()->shoot();
	}
	else if (currentKeyStates[SDL_SCANCODE_RIGHT])
	{
		GameManager::getInstance().getPlayer()->moveRight(4);
	}
	else if (currentKeyStates[SDL_SCANCODE_LEFT])
	{
		GameManager::getInstance().getPlayer()->moveLeft(4);
	}
}
