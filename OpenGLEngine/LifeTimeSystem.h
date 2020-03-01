#pragma once
#include "ECSConfig.h"
#include "LifeTimeComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class LifeTimeSystem : public ECSSystem
	{
	public:
		LifeTimeSystem();
		void Update(float deltaTime);
	};
}
