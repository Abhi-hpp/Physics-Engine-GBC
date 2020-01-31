#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FixedSpringComponent
	{
		FixedSpringComponent(float _springConst = 10.0f, float _restLength = 10.0f, ECSEntity _connectedEntity = NULL) 
			: springConst(_springConst), restLength(_restLength), connectedEntity(_connectedEntity)
		{

		}
		float springConst;
		float restLength;
		ECSEntity connectedEntity;
	};
}
