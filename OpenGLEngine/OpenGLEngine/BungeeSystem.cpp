#include "BungeeSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BungeeSystem::BungeeSystem()
	{
		requireComponent<BungeeComponent>();
		requireComponent<TransformComponent>();
	}

	void BungeeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& bungeeTransform = e.getComponent<TransformComponent>();
			auto& bungee = e.getComponent<BungeeComponent>();

			if (bungee.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& bungee.connectedEntity.hasComponent<TransformComponent>())
			{
				auto& forceAcc = bungee.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto& transform = bungee.connectedEntity.getComponent<TransformComponent>();

				Vector3 relativePosition = transform.position - bungeeTransform.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - bungee.restLength;
					Vector3 force = -glm::normalize(relativePosition);
					force *= bungee.springConstant * deltaL;

					if (length > bungee.restLength)
					{
						forceAcc.AddForce(force);
					}

					float g = 1.0f / (1.0f + pow(abs(deltaL), 0.5f));
					float r = 1 - g;
					Color col = Color(r, g, 0, 1);

					float deltaLength = length / 10.0f;
					Vector3 direction = -glm::normalize(relativePosition);

					for (int i = 0; i < 10; i++)
					{
						getWorld().data.renderUtil->DrawCube(transform.position + (float)i * deltaLength * direction, Vector3(1.0f, 1.0f, 1.0f) * min((bungee.restLength / 20.0f), 100.0f), Vector3(0, 0, 0), col);
					}
					
					getWorld().data.renderUtil->DrawLine(bungeeTransform.position, transform.position, col);
				}
			}
		}
	}
}