#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BoatSimulatorComponent
	{
<<<<<<< Updated upstream
		BoatSimulatorComponent(Vector3 _propulsion = Vector3(0.0f ,0.0f, 1200.0f))
=======
		BoatSimulatorComponent(Vector3 _propulsion = Vector3(0.0f ,0.0f, 1300.0f))
>>>>>>> Stashed changes
			:propulsion(_propulsion)
		{

		}
		Vector3 propulsion;
	};
}
