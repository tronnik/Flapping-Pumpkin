#pragma once

#include "player/player.h"
#include "obstacle/obstacle.h"


namespace Game
{
	void initGame();

	void updateGame();

	void colision(player::createPlayer& player );

	void drawGame();

	void unloadGame();
}
