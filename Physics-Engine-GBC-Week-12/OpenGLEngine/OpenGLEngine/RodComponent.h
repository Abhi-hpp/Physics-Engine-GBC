#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RodComponent
	{
		RodComponent(ECSEntity a = ECSEntity(),
			ECSEntity b = ECSEntity(),
			float _rodLength = 10)
			: entityA(a),
			entityB(b),
			rodLength(_rodLength)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		float rodLength;
	};
}
