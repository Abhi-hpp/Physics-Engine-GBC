#include "PairedSpringSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"
namespace Reality
{
	PairedSpringSystem::PairedSpringSystem()
	{
		requireComponent<PairedSpringComponent>();
	}

	void PairedSpringSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto spring = e.getComponent<PairedSpringComponent>();

			if (spring.connectedEntityA.hasComponent<TransformComponent>()
				&& spring.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto positionA = spring.connectedEntityA.getComponent<TransformComponent>().position;
				auto positionB = spring.connectedEntityB.getComponent<TransformComponent>().position;

				Vector3 relativePos = positionA - positionB;
				float length = glm::length(relativePos);
				float deltaL = length - spring.restLength;

				Vector3 force = (spring.springConstant * deltaL * -glm::normalize(relativePos));

				if (spring.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
				{
					spring.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
				}
				if (spring.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
				{
					spring.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
				}

				getWorld().data.renderUtil->DrawLine(positionA, positionB, Color::Green);
			}
		}
	}
}
