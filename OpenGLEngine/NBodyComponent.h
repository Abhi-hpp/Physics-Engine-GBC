#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct NBodyComponent
	{
		NBodyComponent(float _G = 1.0f)
			: G(_G)
		{

		}

		float G;
	};
}
