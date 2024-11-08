#pragma once

#include "raylib.h"

namespace player
{
	struct  createPlayer
	{
		Rectangle playerbody;

		float gravity = 0.0f;

		float speed = 0.0f;

		int lives = 0;;

		bool alive = 0;;
	};

	void initPlayer(createPlayer& player);
	void movePlayer(createPlayer& player);
}
