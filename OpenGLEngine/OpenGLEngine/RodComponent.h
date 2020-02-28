#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RodComponent
	{
		RodComponent(ECSEntity _entityA = ECSEntity(), ECSEntity _entityB = ECSEntity(), float _rodLength = 10)
			: entityA(_entityA), entityB(_entityB), rodLength(_rodLength)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		float rodLength;
	};
}