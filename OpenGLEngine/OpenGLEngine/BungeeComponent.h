#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BungeeComponent
	{
		BungeeComponent(float _springConstant = 10, float _restLength = 10, ECSEntity _connectedEntity = ECSEntity())
			: springConstant(_springConstant), restLength(_restLength), connectedEntity(_connectedEntity)
		{

		}
		float springConstant;
		float restLength;
		ECSEntity connectedEntity;
		Vector3 finalPosition;
	};
}
