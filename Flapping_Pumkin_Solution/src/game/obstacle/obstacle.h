#pragma once

#include "raylib.h"

namespace obstacle
{
	struct  CreateObstacle
	{
		Vector2 position;
		Vector2 speed;
		int width;
		int topHeight;
		int bottomHeight;
		int gap;
	};

	void initObstacle(CreateObstacle& obstacle);
	void updateObstacle(CreateObstacle& obstacle);
	void drawObstacle(CreateObstacle& obstacle);
}

