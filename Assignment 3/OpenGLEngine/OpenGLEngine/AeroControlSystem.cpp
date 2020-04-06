#include "AeroControlSystem.h"

namespace Reality
{
	AeroControlSystem::AeroControlSystem()
	{
		requireComponent<AeroMinMaxComponent>();
		requireComponent<AeroControlComponent>();
	}

	void AeroControlSystem::Update(float deltaTime)
	{
		pKey = false;
		nKey = false;
		for (auto e : getEntities())
		{
			auto& aero = e.getComponent<AeroMinMaxComponent>();
			auto& control = e.getComponent<AeroControlComponent>();

			for (auto key : control.positiveKeys)
			{
				if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, key) == GLFW_PRESS)
				{
					aero.controlSetting += control.rate * deltaTime;
					pKey = true;
				}
			}
			
			for (auto key : control.negetiveKeys)
			{
				if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, key) == GLFW_PRESS)
				{
					aero.controlSetting -= control.rate * deltaTime;
					nKey = true;
				}
			}

			if (!pKey && !nKey)
			{
				aero.controlSetting = 0;
			}

			aero.controlSetting = glm::clamp(aero.controlSetting, -1.0f, 1.0f);
		}
	}
}
