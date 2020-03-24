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
				getWorld().data.renderUtil->DrawCube(surfaceTransform.GetPosition(),
					Vector3(1, 1, 1),
					surfaceTransform.GetOrientation());

				Vector3 force = CalculateWorldAerodynamicForce(aero.aerodynamicTensor,
					targetTransform, rigidbody.velocity);
				forceAndTorque.AddForceAtPoint(force,
					surfaceTransform.GetPosition(),
					targetTransform.GetPosition());
			}
		}
	}

	const Vector3 & AeroSurfaceSystem::CalculateWorldAerodynamicForce(const Mat3 & localAeroTensor, TransformComponentV2 & transform, const Vector3 & targetVelocity)
	{
		Vector3 localVelocity = transform.WorldToLocalDirection(targetVelocity + windVelocity);
		Vector3 localForce = localAeroTensor * localVelocity;
		return transform.LocalToWorldDirection(localForce);
	}
}
