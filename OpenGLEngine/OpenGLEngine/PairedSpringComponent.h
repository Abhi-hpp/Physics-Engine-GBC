#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PairedSpringComponent
	{
		PairedSpringComponent(float _springConstant = 10.0f,
			float _restLength = 10.0f,
			ECSEntity _connectedEntityA = ECSEntity(),
			ECSEntity _connectedEntityB = ECSEntity())
			: springConstant(_springConstant),
			restLength(_restLength),
			connectedEntityA(_connectedEntityA),
			connectedEntityB(_connectedEntityB)
		{

		}
		float springConstant;
		float restLength;
		ECSEntity connectedEntityA;
		ECSEntity connectedEntityB;
	};
}
