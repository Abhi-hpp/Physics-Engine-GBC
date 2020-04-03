#include "SetAerodynamicTensorSystem.h"

namespace Reality
{
	SetAerodynamicTensorSystem::SetAerodynamicTensorSystem()
	{
		requireComponent<AeroComponent>();
		requireComponent<AeroMinMaxComponent>();
	}

	void SetAerodynamicTensorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& aero = e.getComponent<AeroComponent>();
			auto& minMax = e.getComponent<AeroMinMaxComponent>();

			/*if (minMax.controlSetting <= -1.0f)
			{
				aero.aerodynamicTensor = minMax.minTensor;
			}
			else if (minMax.controlSetting >= 1.0f)
			{
				aero.aerodynamicTensor = minMax.maxTensor;
			}*/
			if (minMax.controlSetting <= 0)
			{
				aero.aerodynamicTensor = -minMax.controlSetting * minMax.minTensor + (minMax.controlSetting + 1) * minMax.baseTensor;
			}
			else if (minMax.controlSetting > 0)
			{
				aero.aerodynamicTensor = (1-minMax.controlSetting) * minMax.baseTensor + minMax.controlSetting * minMax.maxTensor;
			}
			/*else
			{
				aero.aerodynamicTensor = minMax.baseTensor;
			}*/


		}
	}
}
