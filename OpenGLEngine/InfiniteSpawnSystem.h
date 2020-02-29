#pragma once
#include "ECSConfig.h"
#include "InfiniteSpawnComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class InfiniteSpawnSystem : public ECSSystem
	{
	public:
		InfiniteSpawnSystem();
		void Update(float deltaTime);
	};
}
