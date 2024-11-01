#pragma once

#include "raylib.h"

namespace player
{
	struct  createPlayer
	{
		Rectangle playerbody;

		float gravity = 98.0f;

		float jumpSpeed = gravity * 3;

		int lives = 0;;

		bool alive = 0;;
	};

	void initPlayer(createPlayer& player);
	void movePlayer(createPlayer& player);
}
