#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RotateComponentV2
	{
		RotateComponentV2(Vector3 _rotationVelocity = Vector3(0, 0, 0))
			: rotationVelocity(_rotationVelocity)
		{

		}
		Vector3 rotationVelocity;
	};
}
