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
			auto& bungee = e.getComponent<BungeeComponent>();

			if (bungee.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& bungee.connectedEntity.hasComponent<TransformComponent>())
			{
				auto& forceAcc = bungee.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto& transform = bungee.connectedEntity.getComponent<TransformComponent>();

				Vector3 relativePosition = transform.position - springTransform.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - bungee.restLength;

					if (deltaL > 0)
					{
						Vector3 force = -glm::normalize(relativePosition);
						force *= bungee.springConstant * deltaL;
						forceAcc.AddForce(force);
					}

					float g = 1.0f / (1.0f + pow(abs(deltaL), 0.5f));
					if (deltaL < 0)
					{
						g = 1.0f;
					}
					float r = 1 - g;

					Color col = Color(r, g, 0, 1);
				
					float deltaLength = length / 10.0f;
					Vector3 direction = -glm::normalize(relativePosition);
					
					//draw the bungee
					for (int i = 0; i < 10; i++)
					{
						getWorld().data.renderUtil->DrawCube(
							transform.position + (float)i * deltaLength * direction,
							Vector3(1.0f, 1.0f, 1.0f) * min((bungee.restLength / 20.0f), 100.0f), Vector3(0, 0, 0), col);
					}

					getWorld().data.renderUtil->DrawLine(springTransform.position, transform.position,
						col);

				}

			}
		}
	}
}
