#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct SpawnTargetEvent
	{
		SpawnTargetEvent(Vector3 _targetPos =  Vector3(0,0,0))
			:targetPos(_targetPos)
		{

		}
		Vector3 targetPos;
	};
}
