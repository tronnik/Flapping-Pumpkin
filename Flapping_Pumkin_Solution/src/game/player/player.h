#pragma once

#include "raylib.h"

namespace player
{
	struct  createPlayer
	{
		Rectangle playerbody;

		float gravity;

		float speed;

		int lives;

		int points;

		int maxPoints;
	};

	void initPlayer(createPlayer& player);
	void loadSfxPlayer();
	void movePlayer(createPlayer& player);
	void movePlayer2(createPlayer& player2);
}
