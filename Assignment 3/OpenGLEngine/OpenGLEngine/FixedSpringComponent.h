#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FixedSpringComponent
	{
		FixedSpringComponent(float _springConstant = 10, float _restLength = 10, ECSEntity e = ECSEntity())
			:springConstant(_springConstant), restLength(_restLength), entity(e){}
		float springConstant;
		float restLength;
		ECSEntity entity;
	};
}
