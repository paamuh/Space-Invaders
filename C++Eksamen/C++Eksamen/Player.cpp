#include "Player.h"
#include "GameManager.h"
#include <iostream>
#include <chrono>
#include <thread>

Player::Player(int xpos, int ypos, int height, int width, const char * path) : Component(xpos, ypos, height, width, path)
{
	std::cout << "Player created " << std::endl;
}

Player::~Player()
{
}

void Player::displayLives()
{
	lives = GameManager::getInstance().getLives();

	life1C = new Component(30, 30, 20, 50, SPACESHIP_PATH);
	life2C = new Component(100, 30, 20, 50, SPACESHIP_PATH);
	life3C = new Component(170, 30, 20, 50, SPACESHIP_PATH);

	if (lives == 1) {
		life1C->render();
	}
	else if (lives == 2) {
		life2C->render();
		life1C->render();
	}
	else if (lives == 3) {
		life3C->render();
		life2C->render();
		life1C->render();
	}
}

void Player::moveRight(int pace)
{
	if ((rect->x + rect->w) <= GameManager::getInstance().getWindowWidth()) {
		rect->x += pace;
	}
}

void Player::moveLeft(int pace)
{
	if (rect->x >= 0) {
		rect->x -= pace;
	}
}


std::vector <Laser*> Player::getPlayerLaser()
{
	return laser;
}

void Player::erasePlayerLaser(Laser* playerLaser)
{
	int counter = 0;
	for (auto &c : laser)
	{
		if (c == playerLaser)
		{
			laser.erase(laser.begin() + counter);
		}
		counter++;
	}
}

void Player::shoot()
{
	lives = GameManager::getInstance().getLives();
	if (!cooldown && lives > 0) {
		laser.push_back(new Laser(rect->x + 45, rect->y, 10, 10, SPACESHIP_SHOT_PATH));
		cooldown = true;
	}
	gunCooldown();
}

void Player::render()
{
	SDL_RenderCopy(GameManager::getInstance().getRenderer(), texture, nullptr, rect);
	for (auto &playershot : laser) {
		playershot->update();
		playershot->render();
	}
}

void Player::gunCooldown()
{
		unsigned long tempSinceEpoch =
			std::chrono::system_clock::now().time_since_epoch() /
			std::chrono::milliseconds(1);
		if (milliseconds_since_epoch == 0)
		{
			cooldown = false;
			milliseconds_since_epoch = tempSinceEpoch;
		}
		else if ((tempSinceEpoch - milliseconds_since_epoch) >= firerate) {
			cooldown = false;
			milliseconds_since_epoch = tempSinceEpoch;
		}
}