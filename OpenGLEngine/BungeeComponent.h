#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BungeeComponent
	{
		BungeeComponent(bool _isFirst = false, float _springConstant = 0.001f,
			float _restLength = 0.5f,
			ECSEntity _connectedEntity = ECSEntity(),
			ECSEntity _connector = ECSEntity())
			:
			isFirst(_isFirst),
			springConstant(_springConstant),
			restLength(_restLength),
			connectedEntity(_connectedEntity),
			connector(_connector)
		{

		}
		bool isFirst;
		float springConstant;
		float restLength;
		ECSEntity connectedEntity;
		ECSEntity connector;
	};
}
