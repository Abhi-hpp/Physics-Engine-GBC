#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PlaneComponent
	{
		PlaneComponent(ECSEntity _P1 = ECSEntity(), ECSEntity _P2 = ECSEntity(), ECSEntity _P3 = ECSEntity() )
			: point1(_P1), point2(_P2) , point3(_P3)
		{

		}

		ECSEntity point1;
		ECSEntity point2;
		ECSEntity point3;
	};
}
