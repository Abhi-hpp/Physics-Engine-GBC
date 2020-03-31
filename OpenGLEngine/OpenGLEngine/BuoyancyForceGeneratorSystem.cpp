#include "BuoyancyForceGeneratorSystem.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "RigidBodyComponent.h"

namespace Reality
{
	BuoyancyForceGeneratorSystem::BuoyancyForceGeneratorSystem()
	{
		requireComponent<BuoyancyForceGeneratorComponent>();
		requireComponent<TransformComponentV2>();
	}

	void BuoyancyForceGeneratorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{

			auto& hullTransform = e.getComponent<TransformComponentV2>();
			auto& hull = e.getComponent<BuoyancyForceGeneratorComponent>();

			if (hull.attachedEntity.hasComponent<TransformComponentV2>() &&
				hull.attachedEntity.hasComponent<RigidbodyComponent>() &&
				hull.attachedEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{

				auto& targetTransform = hull.attachedEntity.getComponent<TransformComponentV2>();

				SetHullPositionByWorldSurface(targetTransform, hull, hullTransform);

				auto& liquid = e.getComponent<BuoyancyForceGeneratorComponent>().liquid;
				auto& liquidTransform = liquid.getComponent<TransformComponentV2>();

				float depth = hullTransform.GetPosition().y;

				if (depth >= hull.maxDepth + liquidTransform.GetPosition().y)
				{
					return;
				}

				Vector3 force = Vector3(0, 0, 0);

				ModifyForce(depth, liquidTransform, hull, force);

				hull.attachedEntity.getComponent<ForceAndTorqueAccumulatorComponent>().AddForceAtPoint(
					glm::normalize(force),
					hullTransform.GetPosition(),
					targetTransform.GetPosition()
				);

				CreateWaterSurface();
			}
		}
	}

	void BuoyancyForceGeneratorSystem::ModifyForce(float depth, Reality::TransformComponentV2& liquidTransform, Reality::BuoyancyForceGeneratorComponent& hull, Reality::Vector3& force)
	{
		if (depth <= liquidTransform.GetPosition().y - hull.maxDepth)
		{
			force.y = hull.liquidDensity * hull.volume;
		}
		else
		{
			float amountSubmerged = (depth - hull.maxDepth - liquidTransform.GetPosition().y) / (hull.maxDepth * hull.maxDepth);
			force.y = hull.liquidDensity * amountSubmerged * hull.volume;
		}
	}

	void BuoyancyForceGeneratorSystem::CreateWaterSurface()
	{
		getWorld().data.renderUtil->DrawTriangle(Vector3(-100, 0, -100), Vector3(-100, 0, 100), Vector3(100, 0, -100), Color::Blue_Transp);
		getWorld().data.renderUtil->DrawTriangle(Vector3(100, 0, 100), Vector3(-100, 0, 100), Vector3(100, 0, -100), Color::Blue_Transp);
	}

	void BuoyancyForceGeneratorSystem::SetHullPositionByWorldSurface(Reality::TransformComponentV2& targetTransform, Reality::BuoyancyForceGeneratorComponent& hull, Reality::TransformComponentV2& hullTransform)
	{
		Vector3 worldSurfacePosition = targetTransform.LocalToWorldPosition(hull.centerOfBuoyancy);
		hullTransform.SetPosition(worldSurfacePosition);
		hullTransform.SetOrientation(targetTransform.GetOrientation());
	}
}
