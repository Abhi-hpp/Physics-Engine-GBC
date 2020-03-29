#include "BuoyantSpringSystem.h"
#include "ForceAccumulatorComponent.h"
#include "RigidBodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	BuoyantSpringSystem::BuoyantSpringSystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<BuoyantSpringComponent>();
	}

	void BuoyantSpringSystem::Update(float deltaTime)
	{


		for (auto e : getEntities())
		{
			auto& entityTransform = e.getComponent<TransformComponentV2>();
			auto& entityBuoyant = e.getComponent<BuoyantSpringComponent>();
			//auto& entityForceAcc = e.getComponent <ForceAccumulatorComponent>();

			/*int i = 0;
			i++;*/

			getWorld().data.renderUtil->DrawCube(Vector3(0, -5, 50), Vector3(1000, 20, 1000));
			
			if (entityBuoyant.targetEntity.hasComponent<TransformComponentV2>() &&
				entityBuoyant.targetEntity.hasComponent<RigidbodyComponent>() &&
				entityBuoyant.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& targetTransform = entityBuoyant.targetEntity.getComponent<TransformComponentV2>();
				auto& rigidbody = entityBuoyant.targetEntity.getComponent<RigidbodyComponent>();
				auto& forceAndTorque = entityBuoyant.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				// draw Buoyancy
				Vector3 worldBuoyancyPosition = targetTransform.LocalToWorldPosition(entityBuoyant.offset);
				entityTransform.SetPosition(worldBuoyancyPosition);
				entityTransform.SetOrientation(targetTransform.GetOrientation());
				getWorld().data.renderUtil->DrawCube(entityTransform.GetPosition(),
					Vector3(entityBuoyant.maxDepth * 2.0f, entityBuoyant.maxDepth * 2.0f, entityBuoyant.maxDepth * 2.0f),
					entityTransform.GetOrientation());



				float depth = entityTransform.GetPosition().y;



				Vector3 force = Vector3(0.0f, 0.0f, 0.0f);

				if (depth >= height + entityBuoyant.maxDepth)
				{
					force.y = 0.0f;
				}
				else if (depth <= height - entityBuoyant.maxDepth)
				{
					force.y = density * entityBuoyant.volume;
				}
				else
				{
					force.y = (density * entityBuoyant.volume * (entityBuoyant.maxDepth - depth - height) / (2 * entityBuoyant.maxDepth));
				}

				Vector3 AllForce = CalculateBuoyantForce(force, targetTransform);
				forceAndTorque.AddForceAtPoint(force, entityTransform.GetPosition(), targetTransform.GetPosition());
			}
		}
	}
	const Vector3 & BuoyantSpringSystem::CalculateBuoyantForce(const Vector3 & localBuoyancyForce, TransformComponentV2 & transform)
	{
		// TODO: insert return statement here
		return transform.LocalToWorldDirection(localBuoyancyForce);
	}
}
