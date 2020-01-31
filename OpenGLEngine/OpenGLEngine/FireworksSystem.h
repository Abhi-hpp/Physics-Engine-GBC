#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "FireworksComponent.h"

namespace Reality
{
	class FireworksSystem : public ECSSystem
	{
	public:
		FireworksSystem();
		void Update(float deltaTime);
	};
}
