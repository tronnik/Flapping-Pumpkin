#include "obstacle.h"

#include <cstdlib>
#include <ctime>

#include "globals/globals.h"

namespace obstacle
{
	void initObstacle(CreateObstacle& obstacle)
	{
		Globals::Screen.size.y;
		Globals::Screen.size.x;

		obstacle.position = { static_cast<float>(Globals::Screen.size.x),
				   static_cast<float>(0) };

		obstacle.speed = { 500.0f, 0.0f };
		obstacle.width = 30;

		obstacle.gap = 150;

		obstacle.topHeight = GetRandomValue(50, static_cast<int>(Globals::Screen.size.y) - obstacle.gap - 50);
		obstacle.bottomHeight = static_cast<int>(Globals::Screen.size.y) - obstacle.topHeight - obstacle.gap;

		obstacle.passed = false;
	}

	void updateObstacle(CreateObstacle& obstacle)
	{
		if (obstacle.position.x < static_cast<float>(0))
		{
			obstacle.position.x = (Globals::Screen.size.x);
			obstacle.topHeight = GetRandomValue(50, static_cast<int>(Globals::Screen.size.y) - obstacle.gap - 50);
			obstacle.bottomHeight = static_cast<int>(Globals::Screen.size.y) - obstacle.topHeight - obstacle.gap;
			obstacle.passed = false;
		}

		obstacle.position.x -= obstacle.speed.x * GetFrameTime();
	}

}