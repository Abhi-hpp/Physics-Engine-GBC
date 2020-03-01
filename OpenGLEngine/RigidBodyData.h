#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RigidBodyData
	{
		RigidBodyData(ECSEntity _entity)
			:entity(_entity)
		{

		}
		ECSEntity entity;
	};
}
