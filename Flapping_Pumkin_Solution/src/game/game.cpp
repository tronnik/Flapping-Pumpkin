#include "game.h"

#include "raylib.h"

#include "globals/collisionsManager.h"
#include "globals/globals.h"

#include "player/player.h"
#include "obstacle/obstacle.h"

namespace Game
{
	const int maxAmountOfObstacles = 1;
	const float ver = 0.1f;

	player::createPlayer player;
	obstacle::CreateObstacle obstacle;

	bool pause;
	bool gameOver;

	void initGame()
	{
		player::initPlayer(player);
		obstacle::initObstacle(obstacle);

		gameOver = false;
		pause = false;
	}

	void updateGame()
	{
		if (gameOver == true)
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				initGame();
			}
		}

		if (gameOver == false)
		{
			if (player.lives <= 0)
			{
				gameOver = true;
			}

			obstacle.position.x -= obstacle.speed * GetFrameTime();

			if (obstacle.position.x < 0 - obstacle.size.x)
			{
				obstacle::updateObstacle(obstacle);
				obstacle.position.x = Globals::Screen.size.x + obstacle.size.x;
			}

			movePlayer(player);

			if (collisions::rectangleRectangle(player.playerbody.x, player.playerbody.y, player.playerbody.width, player.playerbody.height,
			                                   obstacle.position.x, obstacle.position.y, obstacle.size.x, obstacle.size.y ))
			{
				player.playerbody.y = (Globals::Screen.size.y / 2) - 20;
				player.lives -= 1;
			}
			if (player.playerbody.y > Globals::Screen.size.y - (player.playerbody.height / 2))
			{
				player.playerbody.y = (Globals::Screen.size.y / 2) - 20;
				player.lives -= 1;
			}
		}
	}

	void drawGame()
	{
		DrawRectangle(static_cast<int>(obstacle.position.x), static_cast<int>(obstacle.position.y), static_cast<int>(obstacle.size.x), static_cast<int>(obstacle.size.y), WHITE);
		DrawRectangle(static_cast<int>(player.playerbody.x), static_cast<int>(player.playerbody.y), static_cast<int>(player.playerbody.width), static_cast<int>(player.playerbody.height), WHITE);

		if (gameOver == true)
	    {
			DrawText("GameOver, Press enter to replay!", 230, 200, 20, WHITE);
			DrawText("If not, Press esc to exit!", 230, 230, 20, WHITE);
		}
		DrawText(TextFormat("Version: %.1f", ver), 0, 0, 20, WHITE);
	}

	void unloadGame()
	{

	}
}