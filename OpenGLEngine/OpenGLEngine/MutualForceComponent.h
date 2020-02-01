#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct MutualForceComponent
	{
		MutualForceComponent(float _forceScale = 1.0f)
			: forceScale(_forceScale)
		{

		}
		float forceScale;
	};
}
