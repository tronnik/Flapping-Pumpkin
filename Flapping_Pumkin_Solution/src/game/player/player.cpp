#include "player.h"

#include "globals/globals.h"

namespace player
{
	void initPlayer(createPlayer& player)
	{
		player.alive = true;
		player.lives = 3;
		player.gravity = 220;
		player.jumpSpeed = static_cast<float>( player.gravity * 2.5);
		player.playerbody = { 60, (Globals::Screen.size.y / 2) - 20, 40, 40}; 
	}

	void movePlayer(createPlayer& player)
	{
		if (player.playerbody.y < 0 + (player.playerbody.height / 2))
		{
			player.playerbody.y = 0 + player.playerbody.height / 2;
		}

		if (IsKeyDown(KEY_SPACE))
		{
			player.playerbody.y -= player.jumpSpeed * GetFrameTime(); 
		}
		else player.playerbody.y += player.gravity * GetFrameTime();
	}
}

