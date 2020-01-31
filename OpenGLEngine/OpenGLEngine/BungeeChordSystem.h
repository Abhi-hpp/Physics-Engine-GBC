#pragma once
#include "ECSConfig.h"
#include "BungeeChordComponent.h"

namespace Reality
{
	class BungeeChordSystem : public ECSSystem
	{
	public:
		BungeeChordSystem();
		void Update(float deltaTime);
		ECSEntity lastSpawnedEnity;
		bool spawnEnity = false;
	};
}
