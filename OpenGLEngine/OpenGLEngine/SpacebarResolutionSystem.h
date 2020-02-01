#pragma once
#include "ECSConfig.h"
#include "SpawnBungeeEvent.h"

namespace Reality
{
	class SpacebarResolutionSystem : public ECSSystem
	{
	public:
		SpacebarResolutionSystem();
		void Update(float deltaTime);
	private:
		void ExtendBungeeChain(SpawnBungeeEvent& bungee);

		Vector3 spawnPoint;
	};
}
