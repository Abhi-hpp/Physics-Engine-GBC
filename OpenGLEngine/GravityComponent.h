#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct GravityComponent
	{
		GravityComponent(float _gravityScale = 1.0f)
			: gravityScale(_gravityScale)
		{

		}
		float gravityScale;
	};
}
