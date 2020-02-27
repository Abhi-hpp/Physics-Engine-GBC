#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PenetrationDeltaMoveComponent
	{
		PenetrationDeltaMoveComponent() : deltaMove(Vector3(0, 0, 0))
		{

		}
		Vector3 deltaMove;
	};
}
