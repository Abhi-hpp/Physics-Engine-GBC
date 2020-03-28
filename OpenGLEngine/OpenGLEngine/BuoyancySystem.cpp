#include "BuoyancySystem.h"
#include "RigidbodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<BuoyancyComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		//Draw water surface
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -5), Vector3(500, 0, 5));

		for (auto e : getEntities())
		{
			//int i = 0;
			//++i;

			auto& buoyancyTransform = e.getComponent<TransformComponentV2>();
			auto& buoyancy = e.getComponent<BuoyancyComponent>();

			if (buoyancy.targetEntity.hasComponent<TransformComponentV2>() &&
				buoyancy.targetEntity.hasComponent<RigidbodyComponent>() &&
				buoyancy.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& targetTransform = buoyancy.targetEntity.getComponent<TransformComponentV2>();
				auto& rigidbody = buoyancy.targetEntity.getComponent<RigidbodyComponent>();
				auto& forceAndTorque = buoyancy.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();


				// draw buoyancy
				Vector3 worldBuoyancyPosition = targetTransform.LocalToWorldPosition(buoyancy.localOffset);
				buoyancyTransform.SetPosition(worldBuoyancyPosition);
				buoyancyTransform.SetOrientation(targetTransform.GetOrientation());
				getWorld().data.renderUtil->DrawCube(buoyancyTransform.GetPosition(),
					Vector3(buoyancy.maxDepth * 2.f, buoyancy.maxDepth * 2.f, buoyancy.maxDepth * 2.f),
					buoyancyTransform.GetOrientation());



				//Get the Buoyancy's position
				float depth = buoyancyTransform.GetPosition().y;

				//Draw cube
				//getWorld().data.renderUtil->DrawCube(
				//	entityTransform.position/* - Vector3(0, 1, 0) * entityBuoyancy.maxDepth * 0.5f*/,
				//	Vector3(entityBuoyancy.maxDepth * 2.f, entityBuoyancy.maxDepth * 2.f, entityBuoyancy.maxDepth * 2.f),
				//	Vector3(0, 0, 0));


				Vector3 buoyancyForce = Vector3(0.f, 0.f, 0.f);

				//check if entity is out of water
				if (depth >= waterHeight + buoyancy.maxDepth)
				{
					buoyancyForce.y = 0.f;
				}

				//check if entity is at maximum depth
				else if (depth <= waterHeight - buoyancy.maxDepth)
				{
					buoyancyForce.y = liquidDensity * buoyancy.volume;
				}

				//otherwise entity is partly submerged
				else
				{
					buoyancyForce.y = (liquidDensity * buoyancy.volume * (buoyancy.maxDepth - depth - waterHeight)) / (2 * buoyancy.maxDepth);
				}


				Vector3 force = CalculateWorldBuoyancyForce(buoyancyForce, targetTransform);
				forceAndTorque.AddForceAtPoint(force,
					buoyancyTransform.GetPosition(),
					targetTransform.GetPosition());
			}
		}
	}

	const Vector3& BuoyancySystem::CalculateWorldBuoyancyForce(const Vector3& localBuoyancyForce, TransformComponentV2& transform)
	{
		return transform.LocalToWorldDirection(localBuoyancyForce);
	}
}
