#pragma once
#include "ECSConfig.h"


namespace Reality
{
	struct NBodyComponent
	{
		NBodyComponent(float _gravityScale = 1.0f)
			: gravityScale(_gravityScale)
		{

		}
		float gravityScale;
	};
}
