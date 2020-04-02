#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BodyData
	{
		BodyData(ECSEntity _entity = ECSEntity())
			:entity(_entity)
		{

		}
		ECSEntity entity;
	};
}
