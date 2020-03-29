#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "BuoyantSpringComponent.h"

namespace Reality
{
	class BuoyantSpringSystem : public ECSSystem
	{
	public:
		BuoyantSpringSystem();
		void Update(float deltaTime);

		float height = 0.0f;
		float density = 10.0f;

	private:
		const Vector3& CalculateBuoyantForce(const Vector3& localBuoyancyForce, TransformComponentV2& transform);
	};
}
