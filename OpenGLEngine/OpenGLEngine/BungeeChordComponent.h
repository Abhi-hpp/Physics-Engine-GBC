#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BungeeChordComponent
	{
		BungeeChordComponent(float _springConstant = 10.0f, float _restLength = 10.0f, ECSEntity _connectedEntity = ECSEntity())
			: BungeeSpringConstant(_springConstant), BungeeRestLength(_restLength), connectedEntity(_connectedEntity)
		{

		}
		float BungeeSpringConstant;
		float BungeeRestLength;
		ECSEntity connectedEntity;
	};
}
