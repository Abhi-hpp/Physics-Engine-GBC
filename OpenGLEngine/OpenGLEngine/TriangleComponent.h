#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleComponent
	{
		TriangleComponent(ECSEntity _pointA = ECSEntity(), ECSEntity _pointB = ECSEntity(), ECSEntity _pointC = ECSEntity())
		{
			pointA = _pointA;
			pointB = _pointB;
			pointC = _pointC;
		}

		ECSEntity pointA;
		ECSEntity pointB;
		ECSEntity pointC;

	};
}
