#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct GravityForceComponent
	{
		GravityForceComponent(float _gravityScale = 1.0f)
			: gravityScale(_gravityScale)
		{

		}
		float gravityScale;
	};
}
