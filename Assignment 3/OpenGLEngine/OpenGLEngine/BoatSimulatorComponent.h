#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BoatSimulatorComponent
	{
		BoatSimulatorComponent(Vector3 _prop = Vector3(0.0f ,0.0f, 1200.0f))
			:prop(_prop)
		{

		}
		Vector3 prop;
	};
}
