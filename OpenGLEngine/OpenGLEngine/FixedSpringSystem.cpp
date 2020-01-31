#include "FixedSpringSystem.h"
#include "TransformComponent.h"
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
			auto spring = e.getComponent<FixedSpringComponent>();
			auto springPos = e.getComponent<TransformComponent>().position;

			if (spring.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& spring.connectedEntity.hasComponent<TransformComponent>())
			{
				auto& forceAcc = spring.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto position = spring.connectedEntity.getComponent<TransformComponent>().position;

				Vector3 relativePos = position - springPos;
				float length = glm::length(relativePos);
				float deltaL = length - spring.restLength;

				forceAcc.AddForce(spring.springConstant * deltaL * -glm::normalize(relativePos));

				float r = deltaL / spring.restLength;
				float g = 1/r;
				Color color = Color(r, g, 0, 1);
				getWorld().data.renderUtil->DrawLine(springPos, position, color);
			}

		}
	}
}
