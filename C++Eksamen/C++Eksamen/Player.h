#ifndef PLAYER_H
#define PLAYER_H

#include "Component.h"
#include "Laser.h"
#include <vector>


class Player : public Component
{
public:
	Player(int xpos, int ypos, int height, int width, const char * path);
	~Player();

	void moveRight(int velocity);
	void moveLeft(int velocity);
	void shoot();
	void render();
	void gunCooldown();
	void displayLives();
	std::vector <Laser*> getPlayerLaser();
	void erasePlayerLaser(Laser* playerLaser);



private:

	Component *life1C;
	Component *life2C;
	Component *life3C;


	std::vector<Laser *> laser;

	int lives;
	bool cooldown = false;
	unsigned long milliseconds_since_epoch = 0;
	int firerate = 500;     
	const char * SPACESHIP_PATH = "bmp/space.bmp";
	const char * SPACESHIP_SHOT_PATH = "bmp/shot.bmp";

};

#endif // !PLAYER_H




