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
				
					float deltaLength = length / 10.0f;
					Vector3 direction = -glm::normalize(relativePosition);
					
					//draw the bungee
					for (int i = 0; i < 5; i++)
					{
						getWorld().data.renderUtil->DrawCube(
							transform.position + (float)i * deltaLength * direction,
							Vector3(1.0f, 1.0f, 1.0f) * min((bungee.restLength / 20.0f), 100.0f), Vector3(0, 0, 0), Color::Red);
					}

					getWorld().data.renderUtil->DrawLine(springTransform.position, transform.position, Color::Green);

				}

			}
		}
	}
}
