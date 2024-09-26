#pragma once
#include "ECSConfig.h"
#include "NBodyComponent.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	class NBodySystem : public ECSSystem
	{
	public:
		NBodySystem();
		void Update(float deltaTime);
		float gravity = 9.8f;
	};
}
