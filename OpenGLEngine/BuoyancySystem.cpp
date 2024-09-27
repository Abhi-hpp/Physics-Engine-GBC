#include "BuoyancySystem.h"
#include "RigidBodyComponent.h"
#include "GravityForceComponent.h"
//#include "DragForceComponent.h"
#include "TransformComponentV2.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponentV2>();
		//requireComponent<ForceAndTorqueAccumulatorComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { liquidDensity += 0.05f; }
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { liquidDensity -= 0.05f; }

		for (auto e : getEntities())
		{
			//auto& forceAndTorqueAcc = e.getComponent<ForceAndTorqueAccumulatorComponent>();
			auto buoyTransform = e.getComponent<TransformComponentV2>();
			auto buoy = e.getComponent<BuoyancyComponent>();
			if (buoy.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>() &&
				buoy.targetEntity.hasComponent<TransformComponentV2>())
			{
				auto& forceAndTorqueAcc = buoy.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();
				auto& targetTransform = buoy.targetEntity.getComponent<TransformComponentV2>();


				Vector3 buoyancyPos = targetTransform.LocalToWorldPosition(buoy.centerOfBuoyancy);
				buoyTransform.SetPosition(buoyancyPos);
				buoyTransform.SetOrientation(targetTransform.GetOrientation());


				float d = ((buoy.maxDepth / 2) - (buoyancyPos.y - liquidVolume.y)) / buoy.maxDepth;

				Color color = Color::Red;
				if (d <= 0)
				{
					color = Color::Orange;
					//Force = 0 
				}
				else if (d >= 1)
				{
					color = Color::Blue;
					float vp = liquidDensity * buoy.volume;
					Vector3 force = Vector3(0, vp, 0);
					forceAndTorqueAcc.AddForceAtPoint(force, buoyTransform.GetPosition(), targetTransform.GetPosition());
				}
				else // 0 < d < 1
				{
					color = Color::Green;
					float dvp = d * liquidDensity * buoy.volume;
					Vector3 force = Vector3(0, dvp, 0);
					forceAndTorqueAcc.AddForceAtPoint(force, buoyTransform.GetPosition(), targetTransform.GetPosition());
				}

				getWorld().data.renderUtil->DrawSphere(buoyTransform.GetPosition(), buoy.maxDepth, color);
				getWorld().data.renderUtil->DrawSphere(buoyTransform.GetPosition(), buoy.maxDepth, color);

			}
		}
		//Agua
		getWorld().data.renderUtil->DrawCube(glm::vec3(0, -50, 0), glm::vec3(5000, 100, 5000), glm::quat(), Color::Blue);

	}
}
