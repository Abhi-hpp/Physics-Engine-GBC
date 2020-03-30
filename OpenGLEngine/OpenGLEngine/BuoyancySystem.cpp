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
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -10), Vector3(500, 0, -10));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -20), Vector3(500, 0, -20));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -30), Vector3(500, 0, -30));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -40), Vector3(500, 0, -40));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -50), Vector3(500, 0, -50));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -60), Vector3(500, 0, -60));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -70), Vector3(500, 0, -70));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -80), Vector3(500, 0, -80));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -90), Vector3(500, 0, -90));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -100), Vector3(500, 0, -100));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -110), Vector3(500, 0, -110));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -120), Vector3(500, 0, -120));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -130), Vector3(500, 0, -130));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -140), Vector3(500, 0, -140));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -150), Vector3(500, 0, -150));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -160), Vector3(500, 0, -160));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -170), Vector3(500, 0, -170));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -180), Vector3(500, 0, -180));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -190), Vector3(500, 0, -190));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -200), Vector3(500, 0, -200));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -210), Vector3(500, 0, -210));
		getWorld().data.renderUtil->DrawLine(Vector3(-500, 0, -220), Vector3(500, 0, -220));


		for (auto e : getEntities())
		{

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



				//Getting Buoyancy position
				float depth = buoyancyTransform.GetPosition().y;


				Vector3 buoyancyForce = Vector3(0.f, 0.f, 0.f);

				//if entity is out of water
				if (depth >= waterHeight + buoyancy.maxDepth)
				{
					buoyancyForce.y = 0.f;
				}

				//if entity is at maximum depth
				else if (depth <= waterHeight - buoyancy.maxDepth)
				{
					buoyancyForce.y = liquidDensity * buoyancy.volume;
				}

				//entity is partly submerged
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
