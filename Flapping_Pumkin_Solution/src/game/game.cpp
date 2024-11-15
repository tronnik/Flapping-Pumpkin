#include "game.h"

#include "raylib.h"

#include <iostream>

#include "gameManager.h"

#include "globals/collisionsManager.h"
#include "globals/globals.h"

#include "player/player.h"
#include "obstacle/obstacle.h"

namespace Game
{
	const int maxAmountOfObstacles = 1;

	player::createPlayer player1;
	player::createPlayer player2;
	obstacle::CreateObstacle obstacle;

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

	void initGame(bool& twoPlayerOn)
	{
		gameOver = false;
		pause = true;

		player::initPlayer(player1);

		if (twoPlayerOn)
		{

			player::initPlayer(player2);
		}

		obstacle::initObstacle(obstacle);

		ghost = LoadTexture("res/game/ghost.png");
		ghostFrameRec = { 0.0f, 0.0f, static_cast<float>(ghost.width / 8), static_cast<float>(ghost.height) };
		ghostPosition = { player1.playerbody.x - (player1.playerbody.width / 2), player1.playerbody.y - (player1.playerbody.height / 2) };
		ghostCurrentFrame = 0;
		ghostFramesCounter = 0;
		ghostFramesSpeed = 10;

		if (twoPlayerOn)
		{
			ghostFrameRec2 = { 0.0f, 0.0f, static_cast<float>(ghost.width / 8), static_cast<float>(ghost.height) };
			ghostPosition2 = { player2.playerbody.x - (player2.playerbody.width / 2), player2.playerbody.y - (player2.playerbody.height / 2) };
			ghostCurrentFrame2 = 0;
			ghostFramesCounter2 = 0;
			ghostFramesSpeed2 = 10;

		}

		background1 = LoadTexture("res/game/enviroment/layers/1.png");
		background2 = LoadTexture("res/game/enviroment/layers/3.png");
		background3 = LoadTexture("res/game/enviroment/layers/4.png");
		background4 = LoadTexture("res/game/enviroment/layers/5.png");
		background5 = LoadTexture("res/game/enviroment/layers/7.png");

	}

	void updateGame(bool& twoPlayerOn)
	{
		if (gameOver == true)
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				initGame(twoPlayerOn);
			}
			if (IsKeyPressed(KEY_SPACE))
			{
				gameManager::currentscreen = gameManager::menu;
			}
		}

		if (player1.lives <= 0)
		{
			gameOver = true;
		}

		if (twoPlayerOn)
		{
			if (player2.lives <= 0)
			{
				gameOver = true;
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


			if (pause == false)
			{

				ghostFramesCounter++;
				ghostFramesCounter2++;

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
				if (twoPlayerOn)
				{

					if (ghostFramesCounter2 >= (60 / ghostFramesSpeed2))
					{
						ghostFramesCounter2 = 0;
						ghostCurrentFrame2++;

						if (ghostCurrentFrame2 > 5) ghostCurrentFrame2 = 0;

						ghostFrameRec2.x = static_cast<float>(ghostCurrentFrame2) * static_cast<float>(ghost.width) / 8;
					}
				}

				//Move obstacles
				updateObstacle(obstacle);

				movePlayer(player1);
				colision(player1);
				ghostPosition = { player1.playerbody.x - (player1.playerbody.width / 2), player1.playerbody.y - (player1.playerbody.height / 2) };

				if (twoPlayerOn)
				{
					movePlayer2(player2);
					colision(player2);
					ghostPosition2 = { player2.playerbody.x - (player2.playerbody.width / 2), player2.playerbody.y - (player2.playerbody.height / 2) };

				}
			}
		}
	}

	void colision(player::createPlayer& player)
	{
		bool collisionTop = collisions::rectangleRectangle(static_cast<float>(player.playerbody.x), static_cast<float>(player.playerbody.y),
			static_cast<float>(player.playerbody.width), static_cast<float>(player.playerbody.height),
			static_cast<float>(obstacle.position.x), static_cast<float>(obstacle.position.y), static_cast<float>(obstacle.width),
			static_cast<float>(obstacle.topHeight));

		bool collisionBottom = collisions::rectangleRectangle(static_cast<float>(player.playerbody.x), static_cast<float>(player.playerbody.y),
			static_cast<float>(player.playerbody.width), static_cast<float>(player.playerbody.height),
			static_cast<float>(obstacle.position.x), static_cast<float>(obstacle.position.y), static_cast<float>(obstacle.width),
			static_cast<float>(obstacle.bottomHeight));

		if (collisionTop || collisionBottom)
		{
			initObstacle(obstacle);
			player.lives--;
			pause = true;
		}

		if (player.playerbody.y > Globals::Screen.size.y - (player.playerbody.height / 2))
		{
			player.playerbody.y = (Globals::Screen.size.y / 2) - 20;
			player.lives--;
			pause = true;
		}


	}

	void drawGame(bool& twoPlayerOn)
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

		drawObstacle(obstacle);



		if (gameOver == true)
		{
			DrawText("GameOver, Press enter to replay!", 230, 200, 20, WHITE);
			DrawText("If not, Press space for menu!", 230, 230, 20, WHITE);
			DrawText("or Press esc to exit!", 230, 260, 20, WHITE);
		}
		if (pause == true && gameOver == false)
		{
			DrawText("Pause On, Press SPACE to play!", 230, 200, 20, WHITE);
			DrawText("Press spacebar to move player 1 (white ghost)", 230, 250, 20, WHITE);
			DrawText("Press arrow up to move player 2 (red ghost)", 230, 300, 20, WHITE);
		}

		DrawTextureRec(ghost, ghostFrameRec, ghostPosition, WHITE);

		if (twoPlayerOn)
		{
			DrawTextureRec(ghost, ghostFrameRec2, ghostPosition2, RED);

		}

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