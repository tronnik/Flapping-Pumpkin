#include "globals.h"

#include "raylib.h"

namespace Globals
{
	CreateScreen Screen;

	void initGlobals()
	{
		Screen.name = "Flappin Halloween";
		Screen.size = { 800, 600 };
	}
}
