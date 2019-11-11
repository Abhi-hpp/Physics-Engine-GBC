#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "DynamicPointLightComponent.h"
namespace Reality
{
	class DynamicPointLightSystem : public ECSSystem
	{
	public:
		DynamicPointLightSystem();
		void Update(float deltaTime);
	private:
		std::vector<PointLight> lights;
	};
}
