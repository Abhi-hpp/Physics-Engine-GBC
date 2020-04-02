#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct GravityForceComponentV2
	{
		GravityForceComponentV2(float _gravityScale = 1.0f)
			: gravityScale(_gravityScale)
		{

		}

		float gravityScale;
	};
}
