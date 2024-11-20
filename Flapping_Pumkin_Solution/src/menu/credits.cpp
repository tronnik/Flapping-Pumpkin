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

		DrawText("Created by Estanislao!", 20, 30, 20, WHITE);
		DrawText("Created by Valentin!", 20, 70, 20, WHITE);
		DrawText("ghost by ToffeBunny on Itch.io halloween cats", 20, 110, 20, WHITE);
		DrawText("Parallax by craftpix on Itch.io Parallax Halloween 2D Game Backgrounds", 20, 150, 20, WHITE);
		DrawText("Menu Music by Valentin in Suno.ai Haunted Pixels", 20, 190, 20, WHITE);
		DrawText("Menu Music by Valentin in Suno.ai Ghost in the Pixels", 20, 240, 20, WHITE);

		DrawText("jump sfx:", 20, 280, 20, WHITE);
		DrawText("https://www.zapsplat.com/music/cartoon-bounce-drum-tympani-boing/", 120, 280, 19, WHITE);

		DrawText("crush sfx:", 20, 320, 20, WHITE);
		DrawText("https://pixabay.com/es/sound-effects/tin-recycled-161018-0290-81602/", 140, 320, 19, WHITE);

		DrawText("points sfx:", 20, 360, 20, WHITE);
		DrawText("https://pixabay.com/es/sound-effects/cute-level-up-3-189853/", 140, 360, 19, WHITE);

		DrawText("click sfx:", 20, 400, 20, WHITE);
		DrawText("https://www.zapsplat.com/music/apple-computer-mouse-click-1/", 120, 400, 19, WHITE);

		DrawText("game over sfx:", 20, 440, 20, WHITE);
		DrawText("https://www.zapsplat.com/music/8-bit-game-over-80s", 200, 440, 19, WHITE);
		DrawText("-arcade-simple-alert-notification-for-game-1/", 200, 460, 19, WHITE);

		DrawText("EXIT", static_cast<int>(Globals::Screen.size.x) / 2 - 20, 515 , 20, WHITE);
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
		returnBttn.buttonText[0] = LoadTexture("res/menu/base_button.png");
		returnBttn.position = { (Globals::Screen.size.x / 2 - (returnBttn.buttonText[0].width / 2)), 500 };

	}
}