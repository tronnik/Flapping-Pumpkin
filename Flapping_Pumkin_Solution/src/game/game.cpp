#include "game.h"

#include "raylib.h"

#include "gameManager.h"

#include "globals/collisionsManager.h"
#include "globals/globals.h"

#include "player/player.h"
#include "obstacle/obstacle.h"

namespace Game
{
	const int maxAmountOfObstacles = 1;

	player::createPlayer player;
	obstacle::CreateObstacle obstacleDown;

	Texture2D ghost;
	Rectangle ghostFrameRec;
	Vector2 ghostPosition;
	int ghostCurrentFrame;
	int ghostFramesCounter;
	int ghostFramesSpeed;

	bool pause;
	bool gameOver;

	void initGame()
	{
		player::initPlayer(player);
		obstacle::initObstacle(obstacleDown);

		ghost = LoadTexture("res/game/ghostx2.png");
		ghostFrameRec = { 0.0f, 0.0f, static_cast<float>(ghost.width / 8), static_cast<float>(ghost.height) };
		ghostPosition = { player.playerbody.x - (player.playerbody.width / 2), player.playerbody.y - (player.playerbody.height / 2) };
		ghostCurrentFrame = 0;
		ghostFramesCounter = 0;
		ghostFramesSpeed = 8;

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
			if (IsKeyPressed(KEY_SPACE))
			{
				gameManager::CurrentScreen = gameManager::menu;
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

				ghostFramesCounter++;
				if (ghostFramesCounter >= (60 / ghostFramesSpeed))
				{
					ghostFramesCounter = 0;
					ghostCurrentFrame++;

					if (ghostCurrentFrame > 5) ghostCurrentFrame = 0;

					ghostFrameRec.x = (float)ghostCurrentFrame * (float)ghost.width / 8;
				}

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
				ghostPosition = { player.playerbody.x - (player.playerbody.width / 2), player.playerbody.y - (player.playerbody.height / 2) };
			}
		}
	}

	void drawGame()
	{
		DrawRectangle(static_cast<int>(obstacleDown.position.x), static_cast<int>(obstacleDown.position.y), static_cast<int>(obstacleDown.size.x), static_cast<int>(obstacleDown.size.y), RED);
		DrawRectangle(static_cast<int>(player.playerbody.x), static_cast<int>(player.playerbody.y), static_cast<int>(player.playerbody.width), static_cast<int>(player.playerbody.height), RED);

		if (gameOver == true)
	    {
			DrawText("GameOver, Press enter to replay!", 230, 200, 20, WHITE);
			DrawText("If not, Press space for menu!", 230, 230, 20, WHITE);
			DrawText("or Press esc to exit!", 230, 260, 20, WHITE);
		}
		if (pause == true && gameOver == false)
		{
			DrawText("Pause On, Press SPACE to play!", 230, 200, 20, WHITE);
		}

		DrawTextureRec(ghost, ghostFrameRec, ghostPosition, WHITE);
	}

	void unloadGame()
	{
		UnloadTexture(ghost);
	}
}