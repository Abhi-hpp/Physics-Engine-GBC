#pragma once
#include "ECSConfig.h"
#include "BuoyancyForceGeneratorComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class BuoyancyForceGeneratorSystem : public ECSSystem
	{
	public:
		BuoyancyForceGeneratorSystem();
		void Update(float deltaTime);
		void ModifyForce(float depth, Reality::TransformComponentV2& liquidTransform, Reality::BuoyancyForceGeneratorComponent& hull, Reality::Vector3& force);
		void CreateWaterSurface();
		void SetHullPositionByWorldSurface(Reality::TransformComponentV2& targetTransform, Reality::BuoyancyForceGeneratorComponent& hull, Reality::TransformComponentV2& hullTransform);
	};
}
