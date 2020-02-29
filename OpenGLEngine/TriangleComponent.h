#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleComponent
	{
		TriangleComponent(ECSEntity _a = ECSEntity(), ECSEntity _b = ECSEntity(), ECSEntity _c = ECSEntity()):
			a(_a), b(_b), c(_c)
		{

		}
		ECSEntity a;
		ECSEntity b;
		ECSEntity c;
	};
}
