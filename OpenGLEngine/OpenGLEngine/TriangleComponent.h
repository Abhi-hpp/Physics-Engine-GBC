#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleComponent
	{
		TriangleComponent(ECSEntity a = ECSEntity(),
			ECSEntity b = ECSEntity(),
			ECSEntity c = ECSEntity(),
			ECSEntity d = ECSEntity())
			: entityA(a),
			entityB(b),
			entityC(c),
			sphere(d)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		ECSEntity entityC;
		ECSEntity sphere;
	};
}
