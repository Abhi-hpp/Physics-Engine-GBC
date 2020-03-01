#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct TriangleComponent
	{
		TriangleComponent(ECSEntity _e1 = ECSEntity(), ECSEntity _e2 = ECSEntity(), ECSEntity _e3 = ECSEntity())
			: e1(_e1), e2(_e2), e3(_e3)
		{
		
		}
		ECSEntity e1;
		ECSEntity e2;
		ECSEntity e3;
		Vector3 avg;
		Vector3 cross;
	};
}
