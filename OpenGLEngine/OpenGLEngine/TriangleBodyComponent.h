#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleBodyComponent
	{
		TriangleBodyComponent(
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
