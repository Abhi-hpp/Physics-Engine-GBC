#include "BuoyancySystemV2.h"
#include "RigidbodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystemV2::BuoyancySystemV2()
	{
		requireComponent<BuoyancyComponentV2>();
		requireComponent<TransformComponentV2>();
	}

	void BuoyancySystemV2::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& buoyancy = e.getComponent<BuoyancyComponentV2>();
			auto& transform = e.getComponent<TransformComponentV2>();

			// Draw water
			getWorld().data.renderUtil->DrawCube(Vector3(0.0f, 0.0f, 0.0f), Vector3(2000.0f, buoyancy.maxDepth, 2000.0f), Vector3(0.0f, 0.0f, 0.0f), Color::Blue);

			// Get components belonging to attached entity.
			if (buoyancy.attachedEntity.hasComponent<TransformComponentV2>() && buoyancy.attachedEntity.hasComponent<RigidbodyComponent>() && buoyancy.attachedEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& attachedEntityTransform = buoyancy.attachedEntity.getComponent<TransformComponentV2>();
				auto& rigidbody = buoyancy.attachedEntity.getComponent<RigidbodyComponent>();
				auto& forceAndTorqueAcc = buoyancy.attachedEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				// Draw buoyancy point
				Vector3 buoyancyPosition = attachedEntityTransform.LocalToWorldPosition(buoyancy.localOffset);
				transform.SetPosition(buoyancyPosition);
				getWorld().data.renderUtil->DrawSphere(transform.GetPosition(), 2.0f, Color::Green);

				Vector3 force = Vector3(0.0f, 0.0f, 0.0f);

				// Check if entity is out of water
				if (transform.GetPosition().y >= waterHeight + buoyancy.maxDepth)
				{
					force.y = 0.0f;
				}

				// Check if at maximum depth
				else if (transform.GetPosition().y <= waterHeight - buoyancy.maxDepth)
				{
					force.y = liquidDensity * buoyancy.volume;
				}
				else // Partly submerged
				{
					force.y = (liquidDensity * buoyancy.volume * (buoyancy.maxDepth - transform.GetPosition().y - waterHeight)) / (2 * buoyancy.maxDepth);
				}

				force = attachedEntityTransform.LocalToWorldDirection(force);
				forceAndTorqueAcc.AddForceAtPoint(force, transform.GetPosition(), attachedEntityTransform.GetPosition());
			}
		}
	}
}
