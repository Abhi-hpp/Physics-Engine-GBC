#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "LifeTimeComponent.h"

namespace Reality
{
	class LifeTimeSystem : public ECSSystem
	{
	public:
		LifeTimeSystem();
		void Update(float deltaTime);
	};
}
