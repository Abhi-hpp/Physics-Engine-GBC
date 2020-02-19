#include "DynamicSpotLightSystem.h"

namespace Reality
{
	DynamicSpotLightSystem::DynamicSpotLightSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<DynamicSpotLightComponent>();
		lights.resize(MAX_SPOT_LIGHTS);
	}

	void DynamicSpotLightSystem::Update(float deltaTime)
	{
		int i = 0;
		for (auto e : getEntities())
		{
			if (i < MAX_POINT_LIGHTS)
			{
				auto& transform = e.getComponent<TransformComponent>();
				auto& light = e.getComponent<DynamicSpotLightComponent>();
				lights[i].position = Vector4(transform.position, 1);
				lights[i].ambient = Vector4(light.ambient.r, light.ambient.g, light.ambient.b, light.ambient.a);
				lights[i].diffuse = Vector4(light.diffuse.r, light.diffuse.g, light.diffuse.b, light.diffuse.a);
				lights[i].specular = Vector4(light.specular.r, light.specular.g, light.specular.b, light.specular.a);
				lights[i].constant = 1.0f;
				lights[i].linear = 4.48f / light.range;
				lights[i].quadratic = 71.68f / (light.range * light.range);
				glm::mat4 model = glm::mat4(1.0f);
				model = glm::rotate(model, glm::radians(transform.eulerAngles.z), Vector3(0, 0, 1));
				model = glm::rotate(model, glm::radians(transform.eulerAngles.y), Vector3(0, 1, 0));
				model = glm::rotate(model, glm::radians(transform.eulerAngles.x), Vector3(1, 0, 0));
				lights[i].direction = model * Vector4(0, 0, 1, 1);
				lights[i].cutOff = glm::cos(glm::radians(light.angle));
				lights[i].outerCutOff = glm::cos(glm::radians(light.angle + light.fallOffAngle));
				//getWorld().data.renderUtil->DrawCube(transform.position, Vector3(1, 1, 1), transform.eulerAngles);
			}
			else
			{
				break;
			}
			i++;
		}
		getWorld().data.renderUtil->UpdateSpotLights(lights, getEntities().size());
	}
}
