#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RotateComponent
	{
		RotateComponent(Vector3 _rotationVelocity = Vector3(0, 0, 0))
			: rotationVelocity(_rotationVelocity)
		{
			
		}
		Vector3 rotationVelocity;
	};
}
