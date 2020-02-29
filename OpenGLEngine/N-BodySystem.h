#pragma once
#include "ECSConfig.h"
#include "N-BodyComponent.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	class N_BodySystem : public ECSSystem
	{
	public:
		N_BodySystem();
		void Update(float deltaTime);
	};
}
