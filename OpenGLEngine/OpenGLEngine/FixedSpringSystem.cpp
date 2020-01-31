#include "FixedSpringSystem.h"

#include "ForceAccumulatorComponent.h"

namespace Reality
{
	FixedSpringSystem::FixedSpringSystem()
	{
		requireComponent<FixedSpringComponent>();
		requireComponent<TransformComponent>();
	}

	void FixedSpringSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& spring = e.getComponent<FixedSpringComponent>();

			auto& springTransform = e.getComponent<TransformComponent>();

			if (spring.connectedEntity.hasComponent<TransformComponent>() && spring.connectedEntity.hasComponent<ForceAccumulatorComponent>())
			{
				auto& transform = spring.connectedEntity.getComponent<TransformComponent>();
				auto& forceAcc = spring.connectedEntity.getComponent<ForceAccumulatorComponent>();

				Vector3 relativePosition = transform.position - springTransform.position;
				float length = glm::length(relativePosition);
				if (length > spring.restLength)
				{
					float deltaL = length - spring.restLength;
					Vector3 force = -glm::normalize(relativePosition);
					force *= spring.springConst * deltaL;
					forceAcc.AddForce(force);
					if (DEBUG_LOG_LEVEL > 0)
					{
						getWorld().data.renderUtil->DrawLine(springTransform.position, transform.position, deltaL > 0 ? Color::Red : Color::Green);
						getWorld().data.renderUtil->DrawLine(springTransform.position, transform.position, deltaL > 0 ? Color::Red : Color::Green);
					}
				}

			}
		}
	}
}
