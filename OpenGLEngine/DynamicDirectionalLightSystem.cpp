#include "DynamicDirectionalLightSystem.h"
#include <glm/gtx/euler_angles.hpp> 

namespace Reality
{
	DynamicDirectionalLightSystem::DynamicDirectionalLightSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<DynamicDirectionalLightComponent>();
		lights.resize(MAX_DIR_LIGHTS);
	}

	void DynamicDirectionalLightSystem::Update(float deltaTime)
	{
		int i = 0;
		for (auto e : getEntities())
		{
			if (i < MAX_DIR_LIGHTS)
			{
				auto& transform = e.getComponent<TransformComponent>();
				auto& light = e.getComponent<DynamicDirectionalLightComponent>();
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::rotate(model, glm::radians(transform.eulerAngles.z), Vector3(0, 0, 1));
				model = glm::rotate(model, glm::radians(transform.eulerAngles.y), Vector3(0, 1, 0));
				model = glm::rotate(model, glm::radians(transform.eulerAngles.x), Vector3(1, 0, 0));
				lights[i].direction = model * Vector4(0, 0, 1, 1);
				//lights[i].direction.y *= -1;
				lights[i].ambient = Vector4(light.ambient.r, light.ambient.g, light.ambient.b, light.ambient.a);
				lights[i].diffuse = Vector4(light.diffuse.r, light.diffuse.g, light.diffuse.b, light.diffuse.a);
				lights[i].specular = Vector4(light.specular.r, light.specular.g, light.specular.b, light.specular.a);
			}
			else
			{
				break;
			}
			i++;
		}
		getWorld().data.renderUtil->UpdateDirLights(lights, getEntities().size());
	}
}
