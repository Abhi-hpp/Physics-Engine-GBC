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

			//aero.aerodynamicForce = aero.addedForce;
			//aero.aerodynamicForce.y += RANDOM_FLOAT(-0.5f, 0.5f);

			//if (surfaceTransform.GetPosition().y < -50)
			//{
			//	surfaceTransform.SetPosition(Vector3(surfaceTransform.GetPosition().x, -50, surfaceTransform.GetPosition().z));
			//}

			getWorld().data.renderUtil->RenderText(std::to_string(surfaceTransform.GetPosition().x) + " " + std::to_string(surfaceTransform.GetPosition().y) + " " + std::to_string(surfaceTransform.GetPosition().z), 1500, 600, 0.3f, Color::Red);
			//getWorld().data.renderUtil->RenderText(std::to_string(aero.aerodynamicForce.x) + " " + std::to_string(aero.aerodynamicForce.y) + " " + std::to_string(aero.aerodynamicForce.z), 1500, 600, 0.3f, Color::Red);
			//std::cout << "x: " << aero.aerodynamicForce.x << " y: " << aero.aerodynamicForce.y << " z: " << aero.aerodynamicForce.z << "\n";

			if (aero.targetEntity.hasComponent<TransformComponentV2>() &&
				aero.targetEntity.hasComponent<RigidbodyComponent>() &&
				aero.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& targetTransform = aero.targetEntity.getComponent<TransformComponentV2>();
				auto& rigidbody = aero.targetEntity.getComponent<RigidbodyComponent>();
				auto& forceAndTorque = aero.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				// HACK: For lack of scene graph
				Vector3 worldSurfacePosition = targetTransform.LocalToWorldPosition(aero.localOffset);
				surfaceTransform.SetPosition(worldSurfacePosition);
				surfaceTransform.SetOrientation(targetTransform.GetOrientation());
				getWorld().data.renderUtil->DrawCube(surfaceTransform.GetPosition(), Vector3(1, 1, 1), surfaceTransform.GetOrientation());

				Vector3 force = CalculateWorldAerodynamicForce(aero.aerodynamicForce, targetTransform);
				forceAndTorque.AddForceAtPoint(force, surfaceTransform.GetPosition(), targetTransform.GetPosition());
			}
		}
	}

	const Vector3 & AeroSurfaceSystem::CalculateWorldAerodynamicForce(const Vector3& localAeroForce, TransformComponentV2& transform)
	{
		return transform.LocalToWorldDirection(localAeroForce);
	}
}
