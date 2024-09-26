#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RotateComponent
	{
		RotateComponent(Vector3 _angularVelocity = Vector3(0, 0, 0)) :
			angularVelocity(_angularVelocity)
		{
			
		}

		Vector3 angularVelocity;
	};
}
