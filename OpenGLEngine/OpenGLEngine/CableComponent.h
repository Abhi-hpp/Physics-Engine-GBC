#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct CableComponent
	{
		CableComponent(ECSEntity _entityA = ECSEntity(), ECSEntity _entityB = ECSEntity(), float _maxLength = 10, float _restitution = 1)
			: entityA(_entityA), entityB(_entityB), maxLength(_maxLength), restitution(_restitution)
		{

		}
		ECSEntity entityA;
		ECSEntity entityB;
		float maxLength;
		float restitution;
	};
}