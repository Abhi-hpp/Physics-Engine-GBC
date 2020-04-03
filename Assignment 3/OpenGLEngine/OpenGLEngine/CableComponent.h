#pragma once
#include "ECSConfig.h"
namespace Reality
{
	struct CableComponent
	{
		CableComponent(ECSEntity a = ECSEntity(), ECSEntity b = ECSEntity(), float _maxLength = 10, float _restitution = 1.0f)
			: entityA(a), entityB(b), maxLength(_maxLength), restitution(_restitution){}
		ECSEntity entityA;
		ECSEntity entityB;
		float maxLength;
		float restitution;
	};
}
