#pragma once
#include "ECSConfig.h"

namespace Reality
{
	class TriangleBodySystem : public ECSSystem
	{
	public:
		TriangleBodySystem();
		void Update(float deltaTime);
	};
}
