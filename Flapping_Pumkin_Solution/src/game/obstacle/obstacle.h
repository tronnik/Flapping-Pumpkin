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

	void initObstacle(CreateObstacle& obstacle);
	void updateObstacle(CreateObstacle& obstacle);
}

