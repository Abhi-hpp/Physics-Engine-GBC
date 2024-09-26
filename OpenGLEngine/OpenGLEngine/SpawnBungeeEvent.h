#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct SpawnBungeeEvent
	{
		SpawnBungeeEvent(ECSEntity _entity = ECSEntity()) :
			entity(_entity)
		{

		}

		ECSEntity entity;
	};
}
