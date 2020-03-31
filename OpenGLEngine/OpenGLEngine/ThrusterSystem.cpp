#include "ThrusterSystem.h"
#include "TransformComponentV2.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "LifeTimeComponent.h"

namespace Reality
{
	ThrusterSystem::ThrusterSystem()
	{
		requireComponent<ThrusterComponent>();
	}

	void ThrusterSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& thruster = e.getComponent<ThrusterComponent>();

			if (thruster.attachedEntity.hasComponent<TransformComponentV2>() &&
				thruster.attachedEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& transform = thruster.attachedEntity.getComponent<TransformComponentV2>();
				auto& forceAndTorque = thruster.attachedEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				Vector3 worldThrustDirection = transform.LocalToWorldDirection(thruster.localThrustDirection);
				forceAndTorque.AddForce(worldThrustDirection * thruster.thrust);

				thruster.timer += deltaTime;

				if (thruster.timer > 0.3f)
				{
					auto smokeTrail = getWorld().createEntity();
					smokeTrail.addComponent<TransformComponentV2>(transform.GetPosition() - worldThrustDirection * 10.0f);
					smokeTrail.addComponent<LifeTimeComponent>();
					thruster.timer = 0;
				}
			}
		}
	}
}
