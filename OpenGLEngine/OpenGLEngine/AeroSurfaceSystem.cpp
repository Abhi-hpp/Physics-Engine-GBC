#include "AeroSurfaceSystem.h"
#include "RigidbodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	AeroSurfaceSystem::AeroSurfaceSystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<AeroSurfaceComponent>();
	}

	void AeroSurfaceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& surfaceTransform = e.getComponent<TransformComponentV2>();
			auto& aero = e.getComponent<AeroSurfaceComponent>();

			GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;

			if (aero.targetEntity.hasComponent<TransformComponentV2>() &&
				aero.targetEntity.hasComponent<RigidbodyComponent>() &&
				aero.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& targetTransform = aero.targetEntity.getComponent<TransformComponentV2>();
				auto& rigidbody = aero.targetEntity.getComponent<RigidbodyComponent>();
				auto& forceAndTorque = aero.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS)
				{
					aero.liquidDensity += 1.0f;
				}
				if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS)
				{
					aero.liquidDensity = (aero.liquidDensity <= 0) ? 0 : (aero.liquidDensity - 1.0f);
				}

				// HACK: For lack of scene graph
				Vector3 worldSurfacePosition = targetTransform.LocalToWorldPosition(aero.localOffset);
				surfaceTransform.SetPosition(worldSurfacePosition);
				surfaceTransform.SetOrientation(targetTransform.GetOrientation());
				getWorld().data.renderUtil->DrawCube(surfaceTransform.GetPosition(),
					Vector3(1, 1, 1),
					surfaceTransform.GetOrientation());

				Vector3 relativePosition = targetTransform.GetPosition() - surfaceTransform.GetPosition();
				float depth = glm::length(relativePosition);


				if (depth > 0)
				{

					if (depth <= aero.waterHeight && insindeWater == true)
					{
						targetTransform.SetPosition(aero.finalPos);
						forceAndTorque.ResetForceAccumulatorY();
						stopMoving = true;
					}

					if (depth >= aero.waterHeight && stopMoving == false)
					{
						insindeWater = true;
						if (depth > aero.waterHeight && (depth <= (aero.waterHeight + aero.maxDepth)))
						{
							Vector3 force = glm::normalize(relativePosition);
							force *= aero.liquidDensity * aero.volume;
							forceAndTorque.AddForce(force);
						}
						if (depth > (aero.waterHeight + aero.maxDepth))
						{
							Vector3 force = -glm::normalize(relativePosition);
							force *= aero.liquidDensity * aero.volume;
							forceAndTorque.AddForce(force);
						}
						aero.finalPos = targetTransform.GetPosition();
					}

					Vector3 force = CalculateWorldAerodynamicForce(aero.aerodynamicForce, targetTransform);
					forceAndTorque.AddForceAtPoint(force,
						surfaceTransform.GetPosition(),
						targetTransform.GetPosition());
				}


				
			}
			getWorld().data.renderUtil->RenderText("Liquid Density : " + std::to_string((int)aero.liquidDensity), 10.0f, 1040.0f, 0.5f, Color(0, 1, 1, 1));
		}
	}

	const Vector3 & AeroSurfaceSystem::CalculateWorldAerodynamicForce(const Vector3& localAeroForce, TransformComponentV2& transform)
	{
		return transform.LocalToWorldDirection(localAeroForce);
	}
}
