#include "Laser.h"
#include <vector>
#include "GameManager.h"



Laser::Laser(int xpos, int ypos, int height, int width, const char * path):Component(xpos, ypos, height, width, path)
{
	
}

Laser::~Laser()
{
}

void Laser::update()
{
	//Speed of the laser shot.
	rect->y -= 14; 
}

void Laser::updateBotLaser()
{
	rect->y +=5;
}

void Laser::render()
{
	SDL_RenderCopy(GameManager::getInstance().getRenderer(), texture, nullptr, rect);
}
