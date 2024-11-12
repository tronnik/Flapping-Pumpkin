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
	player::createPlayer player2;
	obstacle::CreateObstacle obstacleDown;
	obstacle::CreateObstacle obstacleUp;

	Texture2D ghost;
	Rectangle ghostFrameRec;
	Vector2 ghostPosition;
	int ghostCurrentFrame;
	int ghostFramesCounter;
	int ghostFramesSpeed;

	Rectangle ghostFrameRec2;
	Vector2 ghostPosition2;
	int ghostCurrentFrame2;
	int ghostFramesCounter2;
	int ghostFramesSpeed2;

	bool pause;
	bool gameOver;


	Texture2D background1;
	Texture2D background2;
	Texture2D background3;
	Texture2D background4;
	Texture2D background5;
	float scrolling1 = 0.0f;
	float scrolling2 = 0.0f;
	float scrolling3 = 0.0f;
	float scrolling4 = 0.0f;
	float scrolling5 = 0.0f;

	void initGame()
	{
		player::initPlayer(player);
		player::initPlayer(player2);

		obstacle::initObstacleDown(obstacleDown);
		obstacle::initObstacleUp(obstacleUp);

		ghost = LoadTexture("res/game/ghost.png");
		ghostFrameRec = { 0.0f, 0.0f, static_cast<float>(ghost.width / 8), static_cast<float>(ghost.height) };
		ghostPosition = { player.playerbody.x - (player.playerbody.width / 2), player.playerbody.y - (player.playerbody.height / 2) };
		ghostCurrentFrame = 0;
		ghostFramesCounter = 0;
		ghostFramesSpeed = 6;

		ghostFrameRec2 = { 0.0f, 0.0f, static_cast<float>(ghost.width / 8), static_cast<float>(ghost.height) };
		ghostPosition2 = { player2.playerbody.x - (player2.playerbody.width / 2), player2.playerbody.y - (player2.playerbody.height / 2) };
		ghostCurrentFrame2 = 0;
		ghostFramesCounter2 = 0;
		ghostFramesSpeed2 = 6;

		background1 = LoadTexture("res/game/enviroment/layers/1.png");
		background2 = LoadTexture("res/game/enviroment/layers/3.png");
		background3 = LoadTexture("res/game/enviroment/layers/4.png");
		background4 = LoadTexture("res/game/enviroment/layers/5.png");
		background5 = LoadTexture("res/game/enviroment/layers/7.png");

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
				gameManager::currentscreen = gameManager::menu;
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
				ghostFramesCounter2++;

				obstacleDown.position.x -= obstacleDown.speed * GetFrameTime();
				obstacleUp.position.x -= obstacleUp.speed * GetFrameTime();

				scrolling1 -= 100.0f * GetFrameTime();
				scrolling2 -= 150.0f * GetFrameTime();
				scrolling3 -= 200.0f * GetFrameTime();
				scrolling4 -= 250.0f * GetFrameTime();
				scrolling5 -= 300.0f * GetFrameTime();

				if (scrolling1 <= -background1.width / 2) scrolling1 = 0;
				if (scrolling2 <= -background2.width / 2) scrolling2 = 0;
				if (scrolling3 <= -background3.width / 2) scrolling3 = 0;
				if (scrolling4 <= -background4.width / 2) scrolling4 = 0;
				if (scrolling5 <= -background5.width / 2) scrolling5 = 0;


				//Animation player 1
				if (ghostFramesCounter >= (60 / ghostFramesSpeed))
				{
					ghostFramesCounter = 0;
					ghostCurrentFrame++;

					if (ghostCurrentFrame > 5) ghostCurrentFrame = 0;

					ghostFrameRec.x = static_cast<float>(ghostCurrentFrame) * static_cast<float>(ghost.width) / 8;
				}

				//Animation player 2
				if (ghostFramesCounter2 >= (60 / ghostFramesSpeed2))
				{
					ghostFramesCounter2 = 0;
					ghostCurrentFrame2++;
				
					if (ghostCurrentFrame2 > 5) ghostCurrentFrame2 = 0;
				
					ghostFrameRec2.x = static_cast<float>(ghostCurrentFrame2) * static_cast<float>(ghost.width) / 8;
				}

				//Move obstacles
				if (obstacleDown.position.x < 0 - obstacleDown.size.x)
				{
					obstacle::updateObstacleDown(obstacleDown);
				}
				if (obstacleUp.position.x < 0 - obstacleUp.size.x)
				{
					obstacle::updateObstacleUp(obstacleUp);
				}
				

				movePlayer(player);

				movePlayer2(player2);

				//Player 1 collisions
				if (collisions::rectangleRectangle(player.playerbody.x, player.playerbody.y, player.playerbody.width, player.playerbody.height,
					obstacleDown.position.x, obstacleDown.position.y, obstacleDown.size.x, obstacleDown.size.y))
				{
					player.playerbody.y = (Globals::Screen.size.y / 2) - 20;
					player.lives -= 1;
					obstacle::updateObstacleDown(obstacleDown);
					obstacle::updateObstacleUp(obstacleUp);
					pause = true;
				}

				if (collisions::rectangleRectangle(player.playerbody.x, player.playerbody.y, player.playerbody.width, player.playerbody.height,
					obstacleUp.position.x, obstacleUp.position.y, obstacleUp.size.x, obstacleUp.size.y))
				{
					player.playerbody.y = (Globals::Screen.size.y / 2) - 20;
					player.lives -= 1;
					obstacle::updateObstacleDown(obstacleDown);
					obstacle::updateObstacleUp(obstacleUp);
					pause = true;
				}

				if (player.playerbody.y > Globals::Screen.size.y - (player.playerbody.height / 2))
				{
					player.playerbody.y = (Globals::Screen.size.y / 2) - 20;
					player.lives -= 1;
					obstacle::updateObstacleDown(obstacleDown);
					obstacle::updateObstacleUp(obstacleUp);
					pause = true;
				}
				ghostPosition = { player.playerbody.x - (player.playerbody.width / 2), player.playerbody.y - (player.playerbody.height / 2) };
				ghostPosition2 = { player2.playerbody.x - (player2.playerbody.width / 2), player2.playerbody.y - (player2.playerbody.height / 2) };
			}
		}
	}

	void drawGame()
	{
		DrawTextureEx(background1, Vector2{ scrolling1, 20 }, 0.0f, 0.5f, WHITE);
		DrawTextureEx(background1, Vector2{ background1.width / 2 + scrolling1, 20 }, 0.0f, 0.5f, WHITE);

		DrawTextureEx(background2, Vector2{ scrolling2, 20 }, 0.0f, 0.5f, WHITE);
		DrawTextureEx(background2, Vector2{ background2.width / 2 + scrolling2, 20 }, 0.0f, 0.5f, WHITE);

		DrawTextureEx(background3, Vector2{ scrolling3, 20 }, 0.0f, 0.5f, WHITE);
		DrawTextureEx(background3, Vector2{ background3.width / 2 + scrolling3, 20 }, 0.0f, 0.5f, WHITE);

		DrawTextureEx(background4, Vector2{ scrolling4, 20 }, 0.0f, 0.5f, WHITE);
		DrawTextureEx(background4, Vector2{ background4.width / 2 + scrolling4, 20 }, 0.0f, 0.5f, WHITE);

		DrawTextureEx(background5, Vector2{ scrolling5, 20 }, 0.0f, 0.5f, WHITE);
		DrawTextureEx(background5, Vector2{ background5.width / 2 + scrolling5, 20 }, 0.0f, 0.5f, WHITE);


		DrawRectangle(static_cast<int>(obstacleDown.position.x), static_cast<int>(obstacleDown.position.y), static_cast<int>(obstacleDown.size.x), static_cast<int>(obstacleDown.size.y), RED);
		DrawRectangle(static_cast<int>(obstacleUp.position.x), static_cast<int>(obstacleUp.position.y), static_cast<int>(obstacleUp.size.x), static_cast<int>(obstacleUp.size.y), RED);

#ifdef _DEBUG
		DrawRectangle(static_cast<int>(player.playerbody.x), static_cast<int>(player.playerbody.y), static_cast<int>(player.playerbody.width), static_cast<int>(player.playerbody.height), RED);
#endif

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
		//DrawRectangle(static_cast<int>(player2.playerbody.x), static_cast<int>(player2.playerbody.y), static_cast<int>(player2.playerbody.width), static_cast<int>(player2.playerbody.height), RED);
		DrawTextureRec(ghost, ghostFrameRec2, ghostPosition2, RED);
	}

	void unloadGame()
	{
		UnloadTexture(ghost);
		UnloadTexture(background1);
		UnloadTexture(background2);
		UnloadTexture(background3);
		UnloadTexture(background4);
		UnloadTexture(background5);
	}
}