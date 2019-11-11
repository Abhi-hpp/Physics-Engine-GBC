#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "DynamicSpotLightComponent.h"

namespace Reality
{
	class DynamicSpotLightSystem : public ECSSystem
	{
	public:
		DynamicSpotLightSystem();
		void Update(float deltaTime);
	private:
		std::vector<SpotLight> lights;
	};
}
