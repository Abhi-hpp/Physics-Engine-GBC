#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct WindThrusterComponent
	{
		WindThrusterComponent(ECSEntity _targetEntity = ECSEntity(),
			Vector3 _localWindDirection = Vector3(0, 0, 1),
			float _wind = 10, 
			Vector3 _sailPosition = Vector3(0,0,0))
			:attachedEntity(_targetEntity),
			localWindDirection(_localWindDirection),
			wind(_wind),
			sailPosition(_sailPosition)
		{

		}
		ECSEntity attachedEntity;
		Vector3 localWindDirection;
		float wind;
		float timer = 0;
		Vector3 sailPosition;
	};
}
