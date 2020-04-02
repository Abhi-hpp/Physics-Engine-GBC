#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AeroSurfaceComponent
	{
		AeroSurfaceComponent(ECSEntity _targetEntity = ECSEntity(), Vector3 _aerodynamicForce = Vector3(0, 0, 0),
			Vector3 _localOffset = Vector3(0, 0, 0))
			:targetEntity(_targetEntity),
			aerodynamicForce(_aerodynamicForce),
			localOffset(_localOffset)
		{

		}
		ECSEntity targetEntity;
		Vector3 aerodynamicForce;
		Vector3 localOffset;
	};
}
