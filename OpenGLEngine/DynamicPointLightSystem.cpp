#include "DynamicPointLightSystem.h"
#include <glm/gtx/euler_angles.hpp> 

namespace Reality
{
	DynamicPointLightSystem::DynamicPointLightSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<DynamicPointLightComponent>();
		lights.resize(MAX_POINT_LIGHTS);
	}

	void DynamicPointLightSystem::Update(float deltaTime)
	{
		int i = 0;
		for (auto e : getEntities())
		{
			if (i < MAX_POINT_LIGHTS)
			{
				auto& transform = e.getComponent<TransformComponent>();
				auto& light = e.getComponent<DynamicPointLightComponent>();
				lights[i].position = Vector4(transform.position, 1);
				lights[i].ambient = Vector4(light.ambient.r, light.ambient.g, light.ambient.b, light.ambient.a);
				lights[i].diffuse = Vector4(light.diffuse.r, light.diffuse.g, light.diffuse.b, light.diffuse.a);
				lights[i].specular = Vector4(light.specular.r, light.specular.g, light.specular.b, light.specular.a);
				lights[i].constant = 1.0f;
				lights[i].linear = 4.48f / light.radius;
				lights[i].quadratic = 71.68f / (light.radius * light.radius);
				//getWorld().data.renderUtil->DrawCube(transform.position, Vector3(1, 1, 1));
			}
			else
			{
				break;
			}
			i++;
		}
		getWorld().data.renderUtil->UpdatePointLights(lights, getEntities().size());
	}
}
