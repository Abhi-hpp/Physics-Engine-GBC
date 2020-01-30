#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct BuoyantSpringComponent
	{
		BuoyantSpringComponent(float _springConstant = 10.0, float _restLength = 10.0f,
			float _maxDepth = 20.0f, float _volume = 10.0f, float _waterHeight = 0.0f, float _liquidDensity = 20.0f, 
			ECSEntity _connectedEntityA = ECSEntity(), ECSEntity _connectedEntityB = ECSEntity())
			: springConstant(_springConstant), restLength(_restLength), maxDepth(_maxDepth), 
			volume(_volume), waterHeight(_waterHeight), liquidDensity(_liquidDensity), 
			connectedEntityA(_connectedEntityB), connectedEntityB(_connectedEntityB)
		{

		}
		float springConstant;
		float restLength;

		float maxDepth;
		float volume;
		float waterHeight;
		float liquidDensity;

		ECSEntity connectedEntityA;
		ECSEntity connectedEntityB;
	};
}
