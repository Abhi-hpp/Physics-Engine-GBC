#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PlayerSpawnComponent
	{
		PlayerSpawnComponent()
		{

		}

		int lowerX = -10;
		int upperX = 10;

		int lowerZ = -5;
		int upperZ = 10;

		int height = 17;
	};
}
