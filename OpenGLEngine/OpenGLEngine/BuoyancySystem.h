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
		
		// how large the water volume is that the objects interact with
		Vector3 waterDimensions = Vector3(10000, 5000, 10000);
	private:
		float elapsedTime = 0.0f;
		Vector3 Lerp(Vector3 a, Vector3 b, float t );

	};
}
