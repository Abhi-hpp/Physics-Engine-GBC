#pragma once
#include "ECSConfig.h"
#include "NBodyComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	class NBodySystem : public ECSSystem
	{
	public:
		NBodySystem();
		void Update(float deltaTime);
		float gravityConstant = 3.0f;
		Vector3 centerPoint = Vector3(0.0f);
		float mass = 250.0f;
	};
}
