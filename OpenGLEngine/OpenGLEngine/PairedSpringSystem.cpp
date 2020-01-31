#include "PairedSpringSystem.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	PairedSpringSystem::PairedSpringSystem()
	{
		requireComponent<PairedSpringComponent>();
		//requireComponent<TransformComponent>();
	}

	void PairedSpringSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& spring = e.getComponent<PairedSpringComponent>();

			auto& springTransform = e.getComponent<TransformComponent>();

			if (spring.connectedEntity1.hasComponent<TransformComponent>() && spring.connectedEntity1.hasComponent<ForceAccumulatorComponent>()
				&& spring.connectedEntity2.hasComponent<TransformComponent>() && spring.connectedEntity2.hasComponent<ForceAccumulatorComponent>())
			{
				auto& transformA = spring.connectedEntity1.getComponent<TransformComponent>();
				auto& transformB = spring.connectedEntity2.getComponent<TransformComponent>();
				//auto& forceAcc = spring.connectedEntity.getComponent<ForceAccumulatorComponent>();

				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - spring.restLength;
					Vector3 force = -glm::normalize(relativePosition);
					force *= spring.springConst * deltaL;

					if (spring.connectedEntity1.hasComponent<ForceAccumulatorComponent>())
					{
						spring.connectedEntity1.getComponent<ForceAccumulatorComponent>().AddForce(force);
					}
					if (spring.connectedEntity2.hasComponent<ForceAccumulatorComponent>())
					{
						spring.connectedEntity2.getComponent<ForceAccumulatorComponent>().AddForce(-force);
					}

					//forceAcc.AddForce(force);
					if (DEBUG_LOG_LEVEL > 0)
					{
						getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position, deltaL > 0 ? Color::Red : Color::Green);
						getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position, deltaL > 0 ? Color::Red : Color::Green);
					}
				}
			}
		}
	}
}
