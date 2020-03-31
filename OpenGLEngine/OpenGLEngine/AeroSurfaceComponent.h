#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct AeroSurfaceComponent
	{
		AeroSurfaceComponent(ECSEntity _targetEntity = ECSEntity(), Vector3 _aerodynamicForce = Vector3(0, 0, 0),
			Vector3 _localOffset = Vector3(0, 0, 0))
			:attachedEntity(_targetEntity),
			aerodynamicForce(_aerodynamicForce),
			localOffset(_localOffset)
		{

		}
		ECSEntity attachedEntity;
		Vector3 aerodynamicForce;
		Vector3 localOffset;
	};
}
