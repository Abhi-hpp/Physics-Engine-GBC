#include "AeroControlSystem.h"

namespace Reality
{
	AeroControlSystem::AeroControlSystem()
	{
<<<<<<< Updated upstream
		requireComponent<AeroMinMaxComponent>();
=======
		requireComponent<AeroSurfaceComponent>();
>>>>>>> Stashed changes
		requireComponent<AeroControlComponent>();
	}

	void AeroControlSystem::Update(float deltaTime)
	{
<<<<<<< Updated upstream
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
=======
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
>>>>>>> Stashed changes
		}
	}
}
