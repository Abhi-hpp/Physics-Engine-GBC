#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleCollisionComponent
	{
		TriangleCollisionComponent(ECSEntity _E1 = ECSEntity(), ECSEntity _E2 = ECSEntity(), ECSEntity _E3 = ECSEntity())
			: E1(_E1), E2(_E2), E3(_E3)
		{
			
		}

		ECSEntity E1;
		ECSEntity E2;
		ECSEntity E3;
	};
}
