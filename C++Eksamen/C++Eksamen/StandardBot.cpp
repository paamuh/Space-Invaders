#include "StandardBot.h"
#include <iostream>


StandardBot::StandardBot(int xpos, int ypos, int height, int width, int dir, int pace, const char * path) : Component(xpos, ypos, height, width, path)
{
	direction = dir;
	speed = pace;
}

StandardBot::~StandardBot()
{
}

void StandardBot::update()
{
	switch (direction)
	{
	case 0:
		break;
	case 1:
		rect->x -= speed;
		break; //Left
	case 2:
		rect->y += speed;
		break; //Down
	case 3:
		rect->x += speed;
		break; // Right
	case 4:
		rect->y -= speed;
	default:   // UP
		break;
	}
}

void StandardBot::setDirection(int dir)
{
	direction = dir;
}

void StandardBot::setVelocity(int pace)
{
	speed = pace;
}

void StandardBot::moveDown(int pixels)
{
	rect->y += pixels;
}
