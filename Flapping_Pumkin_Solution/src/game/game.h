#pragma once

#include "player/player.h"
#include "obstacle/obstacle.h"


namespace Game
{
	void initGame(bool& twoPlayerOn);

	void updateGame(bool& twoPlayerOn);

	void colision(player::createPlayer& player );

	void drawGame(bool& twoPlayerOn);

	void unloadGame();
}
