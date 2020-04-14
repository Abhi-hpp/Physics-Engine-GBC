#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RodComponent
	{
		RodComponent(ECSEntity a = ECSEntity(), ECSEntity b = ECSEntity(), float _length = 10)
			: entityA(a), entityB(b), length(_length)
		{}
		ECSEntity entityA;
		ECSEntity entityB;
		float length;
	};
}
