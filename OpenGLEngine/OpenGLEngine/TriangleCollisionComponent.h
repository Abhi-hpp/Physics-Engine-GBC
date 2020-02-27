#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleCollisionComponent
	{
		TriangleCollisionComponent(ECSEntity _p1 = ECSEntity(), ECSEntity _p2 = ECSEntity(), ECSEntity _p3 = ECSEntity())
			: p1(_p1), p2(_p2), p3(_p3)
		{

		}
		ECSEntity p1;
		ECSEntity p2;
		ECSEntity p3;
	};
}
