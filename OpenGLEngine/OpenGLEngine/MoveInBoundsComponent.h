#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct MoveInBoundsComponent
	{
		MoveInBoundsComponent(Vector3 _velocity = Vector3(1, 1, 1), Vector3 _bounds = Vector3(10, 10, 10))
			:velocity(_velocity), bounds(_bounds)
		{

		}
		Vector3 velocity;
		Vector3 bounds;
	};
}
