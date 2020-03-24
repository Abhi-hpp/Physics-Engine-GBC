#pragma once
#include "ECSConfig.h"
#include "InfiniteSpawnTargetComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class InfiniteSpawnTargetSystem : public ECSSystem
	{
	public:
		InfiniteSpawnTargetSystem();
		void Update(float deltaTime);
	};
}
