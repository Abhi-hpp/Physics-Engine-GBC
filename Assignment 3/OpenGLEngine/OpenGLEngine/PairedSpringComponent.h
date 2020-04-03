#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PairedSpringComponent
	{
		PairedSpringComponent(float _springConstant = 10, float _restLength = 10, ECSEntity a = ECSEntity(), ECSEntity b = ECSEntity())
			:springConstant(_springConstant), restLength(_restLength), entityA(a), entityB(b) {}
		float springConstant;
		float restLength;
		ECSEntity entityA;
		ECSEntity entityB;
	};
}