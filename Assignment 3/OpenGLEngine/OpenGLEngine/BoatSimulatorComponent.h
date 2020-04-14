#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BoatSimulatorComponent
	{
		BoatSimulatorComponent(Vector3 _p = Vector3(0.0f ,0.0f, 1000.0f))
			:p(_p)
		{

		}
		Vector3 p;
	};
}
