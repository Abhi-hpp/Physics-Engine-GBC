#pragma once
#include "ECSConfig.h"

/**
* A force generator that applies a spring force, where
* one end is attached to a fixed point in space.
*/

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
		/** Holds the spring constant. */
		float springConstant;
		/** Holds the rest length of the spring. */
		float restLength;
		/** The location of the anchored end of the spring. */
		ECSEntity connectedEntity;
	};
}
