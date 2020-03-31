#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ThrusterComponent
	{
		ThrusterComponent(ECSEntity _targetEntity = ECSEntity(), 
			Vector3 _localThrustDirection = Vector3(0, 0, 1),
			float _thrust = 200)
			:targetEntity(_targetEntity),
			localThrustDirection(_localThrustDirection),
			thrust(_thrust)
		{

		}
		ECSEntity targetEntity;
		Vector3 localThrustDirection;
		float thrust;
		float timer = 0;
	};
}
