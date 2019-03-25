#include "Component.h"
#include "GameManager.h"
#include <iostream>

Component::Component(int height, int width, const char * path)
{
	rect = new SDL_Rect();
	rect->h = height;
	rect->w = width;
	rect->x = 0;
	rect->y = 0;
	loadTexture(path);
}

Component::Component(int xpos, int ypos, int height, int width, const char * path)
{
	rect = new SDL_Rect();
	rect->h = height;
	rect->w = width;
	rect->x = xpos;
	rect->y = ypos;
	loadTexture(path);
}

Component::~Component()
{
}

SDL_Rect * Component::getRect() const
{
	return rect;
}

void Component::loadTexture(const char * path)
{
	SDL_Surface * loadedSurface;
	loadedSurface = SDL_LoadBMP(path);
	if (loadedSurface == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0xFF, 0xFF, 0xFF));

	if (texture != nullptr)
	{
		SDL_DestroyTexture(texture);
		std::cout << "Destroyed old texture" << std::endl;
	}

	texture = SDL_CreateTextureFromSurface(GameManager::getInstance().getRenderer(), loadedSurface);

	SDL_FreeSurface(loadedSurface);

	if (texture == nullptr)
	{
		std::cout << "Texture freed" << std::endl;
		return;
	}
}

void Component::render()
{
	SDL_RenderCopy(GameManager::getInstance().getRenderer(), texture, nullptr, rect);
}
