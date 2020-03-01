#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BridgeRopeComponent
	{
		BridgeRopeComponent(ECSEntity a = ECSEntity(),	ECSEntity b = ECSEntity(), float _maximumLength = 10, float _restitution = 1)
			: entityA(a), entityB(b), maximumLength(_maximumLength), restitution(_restitution)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		float maximumLength;
		float restitution;
	};
}
