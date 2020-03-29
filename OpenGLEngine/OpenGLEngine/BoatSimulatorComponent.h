#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BoatSimulatorComponent
	{
		BoatSimulatorComponent(Vector3 _propulsion = Vector3(0.0f ,0.0f, 1300.0f))
			:propulsion(_propulsion)
		{

		}
		Vector3 propulsion;
	};
}
