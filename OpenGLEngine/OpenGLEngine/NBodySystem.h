#pragma once
#include "ECSConfig.h"
#include "NBodyComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	class NBodySystem : public ECSSystem
	{
	public:
		NBodySystem();
		void Update(float deltaTime);
	};
}
