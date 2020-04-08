#include "BungeeSystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BungeeSystem::BungeeSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BungeeComponent>();
	}

	void BungeeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& springTransform = e.getComponent<TransformComponent>();
			auto& spring = e.getComponent<BungeeComponent>();

			if (spring.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& spring.connectedEntity.hasComponent<TransformComponent>())
			{
				if (!spring.isFirst)
				{
					springTransform.position = spring.connector.getComponent<BungeeComponent>().connectedEntity.getComponent<TransformComponent>().position;
				}

				auto& forceAcc = spring.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto& transform = spring.connectedEntity.getComponent<TransformComponent>();

				transform.position = spring.connectedEntity.getComponent<TransformComponent>().position;

				Vector3 relativePosition = transform.position - springTransform.position;
				
				float length = glm::length(relativePosition);
				if (length > 0)
				{

					float deltaL = length - spring.restLength;
					Vector3 force = -glm::normalize(relativePosition);
					if (deltaL > spring.restLength)
						force *= spring.springConstant * deltaL / 4;
					forceAcc.AddForce(force);

					float g = 1.0f / (1.0f + pow(abs(deltaL), 0.5f));
					float r = 1 - g;

					Color col = Color(r, g, 0, 1);

					float deltaLength = length / 10.0f;
					Vector3 direction = -glm::normalize(relativePosition);
					for (int i = 0; i < 10; i++)
					{
						getWorld().data.renderUtil->DrawCube(
							transform.position + (float)i * deltaLength * direction,
							Vector3(1.0f, 1.0f, 1.0f) * min((spring.restLength / 20.0f), 100.0f), Vector3(0, 0, 0), col);
					}

					getWorld().data.renderUtil->DrawLine(springTransform.position, transform.position,
						col);
				}

			}
		}
	}
}
