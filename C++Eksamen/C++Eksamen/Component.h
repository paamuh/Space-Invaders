#ifndef COMPONENT_H
#define COMPONENT_H
#include "SDL.h"

//#include "SDL_image.h"

class Component
{
public:
	Component(int height, int width, const char * path);
	Component(int xpos, int ypos, int height, int width, const char * path);
	~Component();

	SDL_Rect * getRect() const;
	void loadTexture(const char * path);
	void render();

protected:
	SDL_Texture * texture;
	SDL_Rect * rect;

};

#endif // !COMPONENT



