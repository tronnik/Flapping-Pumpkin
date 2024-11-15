#pragma once
#include "raylib.h"


namespace gameManager
{
	int run(void);
	void stop();

	struct Screen 
	{
		const char* name;
		Vector2 size;
	};

	enum CurrentScreen
	{
		menu,
		game,
		credits,
	};

	extern Screen screen;
	extern CurrentScreen currentscreen;
	extern bool twoPlayerOn;
}
