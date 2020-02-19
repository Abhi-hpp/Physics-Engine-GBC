#include "BungeeSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	Reality::BungeeSystem::BungeeSystem()
	{
		requireComponent<BungeeComponent>();

	}

	void Reality::BungeeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& spring = e.getComponent<BungeeComponent>();

			if (spring.connectedEntityA.hasComponent<TransformComponent>()
				&& spring.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = spring.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = spring.connectedEntityB.getComponent<TransformComponent>();

				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);

				if (length <= spring.restLength)
				{
					return;
				}

				if (length > 0)
				{
					float deltaL = spring.springConstant * (spring.restLength - length);

				
					Vector3 force = -glm::normalize(relativePosition);
					force *= -deltaL;

					if (spring.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
					{
						spring.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					}
					if (spring.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
					{
						spring.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
					}
					
					float g = 1.0f / (1.0f + pow(abs(deltaL), 0.5f));
					float r = 1 - g;

					Color col = Color(r, g, 0, 1);

					float deltaLength = length / 10.0f;
					Vector3 direction = glm::normalize(relativePosition);
					for (int i = 0; i < 10; i++)
					{
						getWorld().data.renderUtil->DrawCube(
							transformB.position + (float)i * deltaLength * direction,
							Vector3(1.0f, 1.0f, 1.0f) * min((spring.restLength / 20.0f), 100.0f), Vector3(0, 0, 0), col);
					}
					getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position,
						col);
				}

			}
		}
	}
}