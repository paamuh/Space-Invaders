#ifndef INPUT_MANAGER_H
#define INPUT_MANAGER_H

#include "SDL.h"

class InputManager
{
public:
	InputManager();
	~InputManager();

	void handleInput();

private:
	SDL_Event sdlEvent;
	Uint8 * currentKeyStates;

};

#endif // !INPUT_MANAGER_H



