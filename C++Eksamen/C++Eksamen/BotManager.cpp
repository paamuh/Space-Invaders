#include "BotManager.h"
#include <string>
#include <iostream>
#include <chrono>

const char * BOT_PATH1 = "bmp/invader1.bmp";
const char * BOT_PATH2 = "bmp/invader1-1.bmp";
const char * BOT_PATH3 = "bmp/invader2-1.bmp";
const char * BOT_PATH4 = "bmp/invader2.bmp";
const char * BOT_PATH5 = "bmp/invader3.bmp";
const char * BOT_PATH6 = "bmp/invader3-1.bmp";
const char * BOT_PATH7 = "bmp/invader4-1.bmp";
const char * BOT_PATH8 = "bmp/invader4.bmp";
const char * BOT_SHOT = "bmp/shot2.bmp";



BotManager::BotManager()
{
}

BotManager::~BotManager()
{
}

void BotManager::initializeStandardBots()
{
	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<StandardBot> newBot(new StandardBot(botStartX, botStartY, 40, 40, 3, 1, BOT_PATH2));
		currentBots.push_back(std::move(newBot));

		std::shared_ptr<StandardBot> idleBot(new StandardBot(botStartX, botStartY, 40, 40, 3, 1, BOT_PATH2));
		botAnim1.push_back(std::move(idleBot));

		std::shared_ptr<StandardBot> flyingBot(new StandardBot(botStartX, botStartY, 40, 40, 3, 1, BOT_PATH1));
		botAnim2.push_back(std::move(flyingBot));

		botStartX += 80;
		if (i == 9 || i == 19 || i == 29)
		{
			botStartX = 300;
			botStartY += 40;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<StandardBot> newBot(new StandardBot(botStartX, botStartY + 20, 40, 40, 3, 1, BOT_PATH4));
		currentBots.push_back(std::move(newBot));

		std::shared_ptr<StandardBot> idleBot(new StandardBot(botStartX, botStartY + 20, 40, 40, 3, 1, BOT_PATH4));
		botAnim1.push_back(std::move(idleBot));

		std::shared_ptr<StandardBot> flyingBot(new StandardBot(botStartX, botStartY + 20, 40, 40, 3, 1, BOT_PATH3));
		botAnim2.push_back(std::move(flyingBot));

		botStartX += 80;
		if (i == 9 || i == 19 || i == 29)
		{
			botStartX = 300;
			botStartY += 40;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<StandardBot> newBot(new StandardBot(botStartX, botStartY + 40, 40, 40, 3, 1, BOT_PATH6));
		currentBots.push_back(std::move(newBot));

		std::shared_ptr<StandardBot> idleBot(new StandardBot(botStartX, botStartY + 40, 40, 40, 3, 1, BOT_PATH6));
		botAnim1.push_back(std::move(idleBot));

		std::shared_ptr<StandardBot> flyingBot(new StandardBot(botStartX, botStartY + 40, 40, 40, 3, 1, BOT_PATH5));
		botAnim2.push_back(std::move(flyingBot));

		botStartX += 80;
		if (i == 9 || i == 19 || i == 29)
		{
			botStartX = 300;
			botStartY += 40;
		}
	}

	for (int i = 0; i < 10; i++)
	{
		std::shared_ptr<StandardBot> newBot(new StandardBot(botStartX, botStartY + 60, 40, 40, 3, 1, BOT_PATH8));
		currentBots.push_back(std::move(newBot));

		std::shared_ptr<StandardBot> idleBot(new StandardBot(botStartX, botStartY + 60, 40, 40, 3, 1, BOT_PATH8));
		botAnim1.push_back(std::move(idleBot));

		std::shared_ptr<StandardBot> flyingBot(new StandardBot(botStartX, botStartY + 60, 40, 40, 3, 1, BOT_PATH7));
		botAnim2.push_back(std::move(flyingBot));

		botStartX += 80;
		if (i == 9 || i == 19 || i == 29)
		{
			botStartX = 300;
			botStartY += 40;
		}
	}
}

void BotManager::updateBots()
{
	for (auto &bot : currentBots)
	{
		if (bot->getRect()->x == 950)
		{
			setBotsDirection(1);
			pushStandardBotsDown(25);
			break;
		}
		else if (bot->getRect()->x == 10)
		{
			setBotsDirection(3);
			pushStandardBotsDown(25);
			break;
		}
	}
	for (auto &bot : botAnim1)
	{
		bot->update();
	}
	for (auto &bot : botAnim2)
	{
		bot->update();
	}
}

void BotManager::renderLaser()
{
	for (auto &shoot : botLaser) {
		shoot->updateBotLaser();
		shoot->render();
	}
}

void BotManager::renderBots()
{
	for (auto &bot : currentBots)
	{
		bot->render();
	}
}

void BotManager::eraseBot(std::shared_ptr<StandardBot>bot)
{	
	std::cout << "Bot: " << bot << std::endl;
	int i = 0;
	for(auto &c : currentBots)
	{
		if (c == bot)
		{
			currentBots.erase(currentBots.begin() + i);
			botAnim1.erase(botAnim1.begin() + i);
			botAnim2.erase(botAnim2.begin() + i);
		}
		i++;
	}
}

void BotManager::shoot()
{
	std::vector <std::shared_ptr<StandardBot>> botsLasers = getCurrentBots();
	for (auto &bots : botsLasers)
	{
		int randomNumber = rand() % 5000;

		if (randomNumber == 10) 
		{
			botLaser.push_back(new Laser(bots->getRect()->x, bots->getRect()->y, 10, 10, BOT_SHOT));
		}
	}
}

void BotManager::eraseBotLaser(Laser* botLasers)
{
	int counter = 0;
	for (auto &c : botLaser)
	{
		if (c == botLasers)
		{
			botLaser.erase(botLaser.begin() + counter);
		}
		counter++;
	}
}

void BotManager::shiftBotAnime()
{
	if (switched)
	{
		currentBots = botAnim1;
	}
	else
	{
		currentBots = botAnim2;
	}
	switched = !switched;
}

std::vector<std::shared_ptr<StandardBot>> BotManager::getCurrentBots()
{
	return currentBots;
}

std::vector<Laser*> BotManager::getBotLaser()
{
	return botLaser;
}

void BotManager::setBotsDirection(int direction)
{
	for (auto &bot : botAnim1)
	{
		bot->setDirection(direction);
	}
	for (auto &bot : botAnim2)
	{
		bot->setDirection(direction);
	}
}

void BotManager::pushStandardBotsDown(int pixels)
{
	for (auto &bot : botAnim1)
	{
		bot->moveDown(pixels);
	}
	for (auto &bot : botAnim2)
	{
		bot->moveDown(pixels);
	}
}

