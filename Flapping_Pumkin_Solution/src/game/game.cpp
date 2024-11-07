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
	obstacle::CreateObstacle obstacleDown;

	bool pause;
	bool gameOver;

	void initGame()
	{
		player::initPlayer(player);
		obstacle::initObstacle(obstacleDown);

		gameOver = false;
		pause = true;
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
			if (pause == true)
			{
				if (IsKeyPressed(KEY_SPACE))
				{
					pause = false;
				}
			}

			if (player.lives <= 0)
			{
				gameOver = true;
			}

			if (pause == false)
			{


				obstacleDown.position.x -= obstacleDown.speed * GetFrameTime();

				if (obstacleDown.position.x < 0 - obstacleDown.size.x)
				{
					obstacle::updateObstacle(obstacleDown);
				}

				movePlayer(player);

				if (collisions::rectangleRectangle(player.playerbody.x, player.playerbody.y, player.playerbody.width, player.playerbody.height,
					obstacleDown.position.x, obstacleDown.position.y, obstacleDown.size.x, obstacleDown.size.y))
				{
					player.playerbody.y = (Globals::Screen.size.y / 2) - 20;
					player.lives -= 1;
					obstacle::updateObstacle(obstacleDown);
					pause = true;
				}
				if (player.playerbody.y > Globals::Screen.size.y - (player.playerbody.height / 2))
				{
					player.playerbody.y = (Globals::Screen.size.y / 2) - 20;
					player.lives -= 1;
					obstacle::updateObstacle(obstacleDown);
					pause = true;
				}
			}
		}
	}

	void drawGame()
	{
		DrawRectangle(static_cast<int>(obstacleDown.position.x), static_cast<int>(obstacleDown.position.y), static_cast<int>(obstacleDown.size.x), static_cast<int>(obstacleDown.size.y), WHITE);
		DrawRectangle(static_cast<int>(player.playerbody.x), static_cast<int>(player.playerbody.y), static_cast<int>(player.playerbody.width), static_cast<int>(player.playerbody.height), WHITE);

		if (gameOver == true)
	    {
			DrawText("GameOver, Press enter to replay!", 230, 200, 20, WHITE);
			DrawText("If not, Press esc to exit!", 230, 230, 20, WHITE);
		}
		if (pause == true && gameOver == false)
		{
			DrawText("Pause On, Press SPACE to play!", 230, 200, 20, WHITE);
		}
		DrawText(TextFormat("Version: %.1f", ver), 0, 0, 20, WHITE);
	}

	void unloadGame()
	{

	}
}