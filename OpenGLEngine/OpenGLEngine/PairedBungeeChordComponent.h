#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct PairedBungeeChordComponent
	{
		PairedBungeeChordComponent(float _springConstant = 10.0f, float _restLength = 10.0f, ECSEntity _connectedEntityA = ECSEntity(), ECSEntity _connectedEntityB = ECSEntity())
			: bungeeSpringConstant(_springConstant), bungeeRestLength(_restLength), connectedEntityA(_connectedEntityA), connectedEntityB(_connectedEntityB)
		{

		}
		float bungeeSpringConstant;
		float bungeeRestLength;
		ECSEntity connectedEntityA;
		ECSEntity connectedEntityB;
	};
}
