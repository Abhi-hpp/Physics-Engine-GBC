#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"

namespace Reality
{
	struct MakingPlankComponent
	{
		MakingPlankComponent(
			ECSEntity _point1 = ECSEntity(), 
			ECSEntity _point2 = ECSEntity(), 
			ECSEntity _point3 = ECSEntity())
			: point1(_point1), point2(_point2), point3(_point3)
		{

		}

		ECSEntity point1;
		ECSEntity point2;
		ECSEntity point3;
	};
}
