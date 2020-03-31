#include "AeroControlSystem.h"

namespace Reality
{
	AeroControlSystem::AeroControlSystem()
	{
		requireComponent<AeroSurfaceComponent>();
		requireComponent<AeroControlComponent>();
	}

	void AeroControlSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& surface = e.getComponent<AeroSurfaceComponent>();
			auto& control = e.getComponent<AeroControlComponent>();

			bool reset = true;

			for (int key : control.positiveKeys)
			{
				if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, key) == GLFW_PRESS)
				{
					control.controlSetting += control.controlSpeed * deltaTime;
					reset = false;
				}
			}

			if (control.controlSetting > 1)
			{
				control.controlSetting = 1;
			}

			for (int key : control.negetiveKeys)
			{
				if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, key) == GLFW_PRESS)
				{
					control.controlSetting -= control.controlSpeed * deltaTime;
					reset = false;
				}
			}

			if (control.controlSetting < -1)
			{
				control.controlSetting = -1;
			}

			if (reset)
			{
				control.controlSetting = 0;
			}

			float t = (control.controlSetting + 1) * 0.5f;
			surface.aerodynamicForce = t * control.aeroMinusOne + (1 - t) * control.aeroPlusOne;			
		}
	}
}
