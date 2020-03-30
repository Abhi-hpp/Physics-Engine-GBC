#pragma once
#include "ECSConfig.h"
#include "BuoyancyComponentV2.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class BuoyancySystemV2 : public ECSSystem
	{
	public:
		BuoyancySystemV2();
		void Update(float deltaTime);

		float waterHeight = 0.0f;
		float liquidDensity = 10.0f;
	};
}
