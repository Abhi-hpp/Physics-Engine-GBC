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
		Vector3 waterDimensions = Vector3(10000, 500, 10000);
	private:
		float elapsedTime = 0.0f;
		Vector3 Lerp(Vector3 a, Vector3 b, float t);

	};
}
