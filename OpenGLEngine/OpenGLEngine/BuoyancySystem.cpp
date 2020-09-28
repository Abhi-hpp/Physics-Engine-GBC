#include "BuoyancySystem.h"
#include "RigidBodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponentV2>();

		waterHeight = 0;
		liquidVolume = Vector3(1000, 0, 1000);
		liquidDensity = 10;
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			if (DEBUG_LOG_LEVEL > 0)
				getWorld().data.renderUtil->DrawCube(Vector3(0, waterHeight, 0), liquidVolume, Vector3(0, 0, 0), Color::Cyan);

			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& buoyancyTransform = e.getComponent<TransformComponentV2>();

			if (buoyancy.targetEntity.hasComponent<TransformComponentV2>() &&
				buoyancy.targetEntity.hasComponent<RigidbodyComponent>() &&
				buoyancy.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& transform = buoyancy.targetEntity.getComponent<TransformComponentV2>();
				auto& forceAcc = buoyancy.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				float edge = liquidVolume.x / 2;

				if (transform.GetPosition().x >= -edge && transform.GetPosition().x <= edge && transform.GetPosition().z >= -edge && transform.GetPosition().z <= edge)
				{
					float depth = transform.GetPosition().y;

					Vector3 force(0, 0, 0);

					if (depth >= waterHeight + buoyancy.maxDepth)
					{
						force.y = 0.0f;
						cout << "\nDepth is above water Force is 0\n";
					}
					else if (depth <= waterHeight - buoyancy.maxDepth)
					{
						force.y = liquidDensity * buoyancy.volume;
						cout << "\nDepth is fully\n";
					}
					else
					{
						float d = (depth - buoyancy.maxDepth - waterHeight) / (2 * buoyancy.maxDepth);
						force.y = liquidDensity * buoyancy.volume * d;// (depth - buoyancy.maxDepth - waterHeight) / 2 * buoyancy.maxDepth;
						//force.y = (liquidDensity * buoyancy.volume * (buoyancy.maxDepth - depth - waterHeight)) / (2 * buoyancy.maxDepth);
						cout << "\nDepth is partial\n";
					}
					Vector3 newforce = CalculateWorldBuoyancyForce(force, transform);
					cout << "\nDepth: " << depth;
					cout << "\nForce x: " << newforce.x;
					cout << "\nForce y: " << newforce.y;
					cout << "\nForce z: " << newforce.z;
					//forceAcc.AddForceAtPoint(newforce, buoyancy.centerOfBuoyancy, transform.GetPosition());
					forceAcc.AddForce(newforce);
				}
			}
		}
	}

	const Vector3& BuoyancySystem::CalculateWorldBuoyancyForce(const Vector3& localBuoyancyForce, TransformComponentV2& transform)
	{
		return transform.LocalToWorldDirection(localBuoyancyForce);
	}
}
