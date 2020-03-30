#include "BuoyancyGeneratorSystem.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "RigidBodyComponent.h"

namespace Reality
{
	BuoyancyGeneratorSystem::BuoyancyGeneratorSystem()
	{
		requireComponent<BuoyancyGeneratorComponent>();
		requireComponent<TransformComponentV2>();
	}

	void BuoyancyGeneratorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& liquid = e.getComponent<BuoyancyGeneratorComponent>().liquid;
			auto& liquidTransform = liquid.getComponent<TransformComponentV2>();
			auto& hullTransform = e.getComponent<TransformComponentV2>(); // Location force is applied to, AKA the hull of the ship, AKA center of buoyancy
			auto& hull = e.getComponent<BuoyancyGeneratorComponent>();

			if (hull.targetEntity.hasComponent<TransformComponentV2>() &&
				hull.targetEntity.hasComponent<RigidbodyComponent>() &&
				hull.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& targetTransform = hull.targetEntity.getComponent<TransformComponentV2>(); // The object that owns the surface(hull).  In this case the ship
				auto& forceAndTorque = hull.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				Vector3 worldSurfacePosition = targetTransform.LocalToWorldPosition(hull.centerOfBuoyancy); // Get the world position of the hull
				hullTransform.SetPosition(worldSurfacePosition); // Update the hull position
				hullTransform.SetOrientation(targetTransform.GetOrientation()); // update hull orientation
				
				// Drawing the location of the center of buoyancy
				getWorld().data.renderUtil->DrawCube(hullTransform.GetPosition(),
					Vector3(1, 1, 1),
					hullTransform.GetOrientation());

				if (DEBUG_LOG_LEVEL > 0)
				{
					int yPos = liquidTransform.GetPosition().y - liquidTransform.GetScale().y * 0.5;
					Vector3 pos = Vector3(liquidTransform.GetPosition().x, yPos, liquidTransform.GetPosition().z);
					// Drawing triangles because they are filled in
					getWorld().data.renderUtil->DrawTriangle(Vector3(-10000, 0, -10000), Vector3(-10000, 0, 10000), Vector3(10000, 0, -10000), Color::Blue);
					getWorld().data.renderUtil->DrawTriangle(Vector3(10000, 0, 10000), Vector3(-10000, 0, 10000), Vector3(10000, 0, -10000), Color::Blue);
				}

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