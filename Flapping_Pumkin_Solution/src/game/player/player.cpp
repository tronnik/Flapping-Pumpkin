#include "player.h"

#include "globals/globals.h"

namespace player
{
	void initPlayer(createPlayer& player)
	{
		player.alive = true;
		player.lives = 3;
		player.gravity = 500.0f;
		player.speed = 0.0f;
		player.playerbody = { 60, (Globals::Screen.size.y / 2) - 20, 40, 40}; 
	}

	void movePlayer(createPlayer& player)
	{
		if (player.playerbody.y < 0 + (player.playerbody.height / 2))
		{
			player.playerbody.y = 0 + player.playerbody.height / 2;
		}

		player.speed += player.gravity * GetFrameTime();

		player.playerbody.y += player.speed * GetFrameTime();

		if (IsKeyDown(KEY_SPACE) || IsKeyDown(KEY_UP))
		{
			player.speed = -200.f;
		}
		
		//
		//if (IsKeyDown(KEY_SPACE))
		//{
		//	player.playerbody.y -= player.jumpSpeed * GetFrameTime(); 
		//}
		//else player.playerbody.y += player.gravity * GetFrameTime();
	}
}

