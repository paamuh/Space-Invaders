#ifndef STANDARD_BOT_H
#define STANDARD_BOT_H

#include "Component.h"

class StandardBot : public Component
{
public:
	StandardBot(int xpos, int ypos, int height, int width, int dir, int pace, const char * path);
	~StandardBot();

	void update();
	void setDirection(int dir);
	void setVelocity(int pace);
	void moveDown(int pixels);

private:
	int direction;
	int speed;

};

#endif // !STANDARD_BOT_H



