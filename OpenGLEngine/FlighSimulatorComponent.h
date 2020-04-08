#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FlighSimulatorComponent
	{
		FlighSimulatorComponent(Vector3 _propulsion = Vector3(0.0f ,0.0f, 1000.0f))
			:propulsion(_propulsion)
		{

		}
		Vector3 propulsion;
	};
}
