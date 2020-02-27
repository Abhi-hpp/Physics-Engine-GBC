#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"

namespace Reality
{
	struct TrianglePlaneComponent
	{
		TrianglePlaneComponent(ECSEntity a = ECSEntity(), ECSEntity b = ECSEntity(), ECSEntity c = ECSEntity())
			: p1(a), p2(b), p3(c)
		{

		}

		ECSEntity p1;
		ECSEntity p2;
		ECSEntity p3;

	};
}
