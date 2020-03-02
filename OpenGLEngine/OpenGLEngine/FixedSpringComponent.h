#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FixedSpringComponent
	{
		FixedSpringComponent(float _springConstant = 10.0f,
			float _restLength = 10.0f,
			ECSEntity _connectedEntity = ECSEntity())
			: springConstant(_springConstant),
			restLength(_restLength),
			connectedEntity(_connectedEntity)
		{

		}
		float springConstant;
		float restLength;
		ECSEntity connectedEntity;
	};
}
