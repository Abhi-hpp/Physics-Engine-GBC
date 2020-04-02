#pragma once
#include "ECSConfig.h"
#include "BuoyancyComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class BuoyancySystem : public ECSSystem
	{
	public:
		BuoyancySystem();
		void Update(float deltaTime);

		float waterHeight;
		Vector3 liquidVolume;
		float liquidDensity;

	private:
		const Vector3& CalculateWorldBuoyancyForce(const Vector3& localBuoyancyForce,
			TransformComponentV2& transform);
	};
}
