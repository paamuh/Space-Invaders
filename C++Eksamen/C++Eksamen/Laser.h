#pragma once
#include "Component.h"



class Laser : public Component
{
public:
	Laser(int xpos, int ypos, int height, int width, const char * path);
	~Laser();

	void update();
	void updateBotLaser();
	void render();

private:
	int fireSpeed = 14; 
};


