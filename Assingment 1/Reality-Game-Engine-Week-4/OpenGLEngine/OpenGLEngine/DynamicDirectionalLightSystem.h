#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "DirectionalLightComponent.h"
namespace Reality
{
	class DynamicDirectionalLightSystem : public ECSSystem
	{
	public:
		DynamicDirectionalLightSystem();
		void Update(float deltaTime);
	private:
		std::vector<DirLight> lights;
	};
}
