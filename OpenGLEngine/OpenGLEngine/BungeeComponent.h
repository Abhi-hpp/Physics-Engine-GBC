#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BungeeComponent
	{
		BungeeComponent(float _springConstant = 10.0f, float _restLength = 10.0f, ECSEntity _connectedEntityA = ECSEntity(), ECSEntity _connectedEntityB = ECSEntity(), ECSEntity _lastEntity = ECSEntity())
			: springConstant(_springConstant), restLength(_restLength), connectedEntityA(_connectedEntityA), connectedEntityB(_connectedEntityB), lastEntity(_lastEntity)
		{

		}
		float springConstant;
		float restLength;
		ECSEntity connectedEntityA;
		ECSEntity connectedEntityB;
		ECSEntity lastEntity; // Remember the last object in the bungee chain
	};
}
