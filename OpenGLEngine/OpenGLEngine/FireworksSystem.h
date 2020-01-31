#pragma once
#include "ECSConfig.h"
#include "FireworksComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	class FireworksSystem : public ECSSystem
	{
	public:
		FireworksSystem();
		void Update(float deltaTime);
	};
}
