#include "player.h"

#include "globals/globals.h"

namespace player
{
	Sound jumpSfx;
	
	void initPlayer(createPlayer& player)
	{
		player.lives = 3;
		player.gravity = 500.0f;
		player.speed = 0.0f;
		player.playerbody = { 60, (Globals::Screen.size.y / 2) - 20, 40, 40}; 
		player.points = 0;
		player.maxPoints = 0;
	}

	void loadSfxPlayer()
	{
		jumpSfx = LoadSound("res/sfx/jump.mp3");
	}

	void movePlayer(createPlayer& player)
	{
		if (player.playerbody.y < 0 + (player.playerbody.height / 2))
		{
			player.playerbody.y = 0 + player.playerbody.height / 2;
		}

		player.speed += player.gravity * GetFrameTime();

		player.playerbody.y += player.speed * GetFrameTime();

		if (IsKeyDown(KEY_SPACE))
		{
			player.speed = -200.f;
			SetSoundVolume(jumpSfx, 0.3f);
			PlaySound(jumpSfx);
		}
	}

	void movePlayer2(createPlayer& player2)
	{
		if (player2.playerbody.y < 0 + (player2.playerbody.height / 2))
		{
			player2.playerbody.y = 0 + player2.playerbody.height / 2;
		}

		player2.speed += player2.gravity * GetFrameTime();

		player2.playerbody.y += player2.speed * GetFrameTime();

		if (IsKeyDown(KEY_UP))
		{
			player2.speed = -200.f;
			SetSoundVolume(jumpSfx, 0.3f);
			PlaySound(jumpSfx);
		}
	}
}

