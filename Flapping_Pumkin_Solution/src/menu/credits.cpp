#include "credits.h"

#include "globals/globals.h"
#include "globals/button.h"
#include "globals/collisionsManager.h"

#include "gameManager.h"
#include "menu/menu.h"


namespace Credits
{
	button::createButton returnBttn;
	Rectangle pointer;

	Vector2 pointerPosition = { 0.0f, 0.0f };

	void initCredits()
	{
		initButtons();
		pointer = { 0, 0, 2, 20 };
	}

	void updateCredits()
	{
		pointerPosition = GetMousePosition();
		pointer.x = pointerPosition.x;
		pointer.y = pointerPosition.y;


		if (collisions::rectangleRectangle(returnBttn.position.x, returnBttn.position.y, static_cast<float>(returnBttn.buttonText[0].width), static_cast<float>(returnBttn.buttonText[0].height), pointerPosition.x, pointerPosition.y, pointer.width, pointer.height))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				gameManager::currentscreen = gameManager::menu;
			}
		}


	}

	void drawCredits()
	{
		DrawTexture(returnBttn.buttonText[returnBttn.buttonFrame], static_cast<int>(returnBttn.position.x), static_cast<int>(returnBttn.position.y), WHITE);

#ifdef _DEBUG
		DrawRectangle(static_cast<int>(pointer.x), static_cast<int>(pointer.y), static_cast<int>(pointer.width), static_cast<int>(pointer.height), RED);
#endif

		DrawText("Created by Estanislao!", 50, 420, 20, WHITE);
		DrawText("Created by Valentin!", 50, 450, 20, WHITE);
		DrawText("ghost by ToffeBunny on Itch.io (link pending)", 50, 480, 20, WHITE);
		DrawText("Parallax by craftpix on Itch.io (link pending)", 50, 510, 20, WHITE);
	}

	void unloadCredits()
	{
		for (int i = 0; i < returnBttn.amountOfFrames; i++)
		{
			UnloadTexture(returnBttn.buttonText[i]);
		}
	}

	void initButtons()
	{
		returnBttn.amountOfFrames = 1;
		returnBttn.buttonText[returnBttn.amountOfFrames];
		returnBttn.buttonFrame = 0;
		returnBttn.buttonText = new Texture2D[returnBttn.amountOfFrames];
		returnBttn.buttonText[0] = LoadTexture("res/menu/return_button.png");
		returnBttn.position = { (Globals::Screen.size.x / 2 - (returnBttn.buttonText[0].width / 2)), 200 };

	}
}