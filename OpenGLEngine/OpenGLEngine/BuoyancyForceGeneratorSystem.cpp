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
			auto& liquid = e.getComponent<BuoyancyForceGeneratorComponent>().liquid;
			auto& liquidTransform = liquid.getComponent<TransformComponentV2>();
			auto& hullTransform = e.getComponent<TransformComponentV2>(); // Location force is applied to, AKA the hull of the ship, AKA center of buoyancy
			auto& hull = e.getComponent<BuoyancyForceGeneratorComponent>();

			if (hull.targetEntity.hasComponent<TransformComponentV2>() &&
				hull.targetEntity.hasComponent<RigidbodyComponent>() &&
				hull.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& targetTransform = hull.targetEntity.getComponent<TransformComponentV2>(); // The object that owns the surface(hull).  In this case the ship
				auto& forceAndTorque = hull.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				Vector3 worldSurfacePosition = targetTransform.LocalToWorldPosition(hull.centerOfBuoyancy); // Get the world position of the hull
				hullTransform.SetPosition(worldSurfacePosition); // Update the hull position
				hullTransform.SetOrientation(targetTransform.GetOrientation()); // update hull orientation
				

				int yPos = liquidTransform.GetPosition().y - liquidTransform.GetScale().y * 0.5;
				Vector3 pos = Vector3(liquidTransform.GetPosition().x, yPos, liquidTransform.GetPosition().z);
				// Drawing triangles because they are filled in
				getWorld().data.renderUtil->DrawTriangle(Vector3(-100, 0, -100), Vector3(-100, 0, 100), Vector3(100, 0, -100), Color::Blue_Transp);
				getWorld().data.renderUtil->DrawTriangle(Vector3(100, 0, 100), Vector3(-100, 0, 100), Vector3(100, 0, -100), Color::Blue_Transp);

				// Buoyancy calculations
				Vector3 force = Vector3(0, 0, 0);
				float depth = hullTransform.GetPosition().y;

				if (depth >= liquidTransform.GetPosition().y + hull.maxDepth)
				{
					return;
				}

				if (depth <= liquidTransform.GetPosition().y - hull.maxDepth)
				{
					force.y = hull.volume * hull.liquidDensity;
				}
				else 
				{

					float amountSubmerged = (depth - hull.maxDepth - liquidTransform.GetPosition().y) / (2 * hull.maxDepth);
					force.y = amountSubmerged * hull.volume * hull.liquidDensity;
				}

				forceAndTorque.AddForceAtPoint(glm::normalize(force),
					hullTransform.GetPosition(),
					targetTransform.GetPosition());
			}
		}
	}
}
