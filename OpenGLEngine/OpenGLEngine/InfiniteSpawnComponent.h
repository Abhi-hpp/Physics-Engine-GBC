#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct InfiniteSpawnComponent
	{
		InfiniteSpawnComponent(float _height = 0)
			: height(_height)
		{

		}
		float height;
	};
}
