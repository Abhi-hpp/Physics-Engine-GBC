#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PairedSpringComponent
	{
		PairedSpringComponent(float _springConst = 10.0f, float _restLength = 10.0f, ECSEntity _connectedEntity1 = NULL, ECSEntity _connectedEntity2 = NULL)
			: springConst(_springConst), restLength(_restLength), connectedEntity1(_connectedEntity1), connectedEntity2(_connectedEntity2)
		{

		}
		float springConst;
		float restLength;
		ECSEntity connectedEntity1;
		ECSEntity connectedEntity2;
	};
}
