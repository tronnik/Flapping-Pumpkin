#pragma once

#include "raylib.h"

namespace obstacle
{
	struct  CreateObstacle
	{
		Vector2 position;
		Vector2 size;

		float speed;

		int stride;
	};

	void initObstacleDown(CreateObstacle& obstacle);
	void initObstacleUp(CreateObstacle& obstacle);
	void updateObstacleDown(CreateObstacle& obstacle);
	void updateObstacleUp(CreateObstacle& obstacle);
}

