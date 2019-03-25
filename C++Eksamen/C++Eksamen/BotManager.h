#ifndef BOT_MANAGER_H
#define BOT_MANAGER_H

#include "StandardBot.h"
#include <memory>
#include <vector>
#include "SDL.h"
#include "Laser.h"


class BotManager
{
public:
	BotManager();
	~BotManager();

	void initializeStandardBots();
	void updateBots();
	void renderBots();
	void renderLaser();
	void eraseBot(std::shared_ptr<StandardBot> bot);

	void shoot();
	
	void shiftBotAnime();
	void eraseBotLaser(Laser* botLasers); 

	std::vector <std::shared_ptr<StandardBot>> getCurrentBots();
	std::vector <Laser*> getBotLaser();

private:

	std::vector<Laser*> botLaser;

	std::vector<std::shared_ptr<StandardBot>> currentBots;
	std::vector<std::shared_ptr<StandardBot>> botAnim1;
	std::vector<std::shared_ptr<StandardBot>> botAnim2;


	void setBotsDirection(int direction);
	void pushStandardBotsDown(int pixels);

	bool bmpSwitch = false;
	bool switched = false;

	int botStartX = 300;
	int botStartY = 25;

};

#endif // !BOT_MANAGER_H



