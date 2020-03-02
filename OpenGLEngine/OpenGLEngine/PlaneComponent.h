#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PlaneComponent
	{
		PlaneComponent(ECSEntity a = ECSEntity(),
			ECSEntity b = ECSEntity(),
			ECSEntity c = ECSEntity())
			: entityA(a),
			entityB(b),
			entityC(c)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		ECSEntity entityC;
	};
}
