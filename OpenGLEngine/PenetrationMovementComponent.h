#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PenetrationMovementComponent
	{
		PenetrationMovementComponent() : deltaMove(Vector3(0, 0, 0))
		{

		}
		Vector3 deltaMove;
	};
}
