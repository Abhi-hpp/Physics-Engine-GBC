#include "AddTorqueFromCameraSystem.h"
#include "LifeTimeComponent.h"

namespace Reality
{
	AddTorqueFromCameraSystem::AddTorqueFromCameraSystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<ForceAndTorqueAccumulatorComponent>();
		requireComponent<AddTorqueFromCameraComponent>();
	}

	void AddTorqueFromCameraSystem::Update(float deltaTime)
	{
		if (!pressed && glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_E) == GLFW_PRESS)
		{
			for (auto e : getEntities())
			{
				auto& transform = e.getComponent<TransformComponentV2>();
				auto& forceAndTorqueAcc = e.getComponent<ForceAndTorqueAccumulatorComponent>();
				auto& addTorqueComp = e.getComponent<AddTorqueFromCameraComponent>();

				Camera& cam = getWorld().data.renderUtil->camera;

				Vector3 torque = glm::cross(cam.Position - transform.GetPosition(), cam.Front * addTorqueComp.torqueScale);
				forceAndTorqueAcc.AddTorque(torque);
			}
			pressed = true;
		}
		else if(glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, GLFW_KEY_E) == GLFW_RELEASE)
		{
			pressed = false;
		}
	}
}
