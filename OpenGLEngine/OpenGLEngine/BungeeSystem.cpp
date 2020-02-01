#include "BungeeSystem.h"

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
			auto& bungee = e.getComponent<BungeeComponent>();
			auto& bungeeTransform = e.getComponent<TransformComponent>();

			if (bungee.connectedEntity.hasComponent<TransformComponent>()
				&& bungee.connectedEntity.hasComponent<ForceAccumulatorComponent>())
			{
				auto& transform = bungee.connectedEntity.getComponent<TransformComponent>();
				auto& forceAcc = bungee.connectedEntity.getComponent<ForceAccumulatorComponent>();

				Vector3 relativePosition = transform.position - bungeeTransform.position;
				float length = glm::length(relativePosition);

				if (length > 0)
				{

					if (length > bungee.restLength)
					{
						float deltaL = length - bungee.restLength;
						Vector3 force = -glm::normalize(relativePosition);
						force *= bungee.springConstant * deltaL;
						forceAcc.AddForce(force);
					}

					if (DEBUG_LOG_LEVEL > 0)
					{
						getWorld().data.renderUtil->DrawLine(bungeeTransform.position, transform.position, length > 0 ? Color::Red : Color::Green);
					}
				}
			}
		}
	}
}
