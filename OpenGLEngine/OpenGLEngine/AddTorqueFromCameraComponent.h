#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AddTorqueFromCameraComponent
	{
		AddTorqueFromCameraComponent(float _torqueScale = 10.0f)
			: torqueScale(_torqueScale)
		{

		}
		float torqueScale;
	};
}
