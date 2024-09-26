#pragma once
#include "ECSConfig.h"
#include "BuoyancyControlEvent.h"
#include "BuoyancySystem.h"

namespace Reality
{
	class BuoyancyResolutionSystem : public ECSSystem
	{
	public:
		BuoyancyResolutionSystem();
		void Update(float deltaTime);
	private:
		void spawnVolume(Vector3 point);
		void incrementDensity();
		void decrementDensity();

		Vector3 spawnPoint;
	};
}
