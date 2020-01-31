#include "BungeeSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BungeeSystem::BungeeSystem()
	{
		requireComponent<BungeeComponent>();
	}

	void BungeeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& bungee = e.getComponent<BungeeComponent>();

			if (bungee.connectedEntityA.hasComponent<TransformComponent>()
				&& bungee.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = bungee.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = bungee.connectedEntityB.getComponent<TransformComponent>();

				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);
				if (length > bungee.restLegnth)
				{
					float deltaL = length - bungee.restLegnth;
					Vector3 force = -glm::normalize(relativePosition);
					force *= bungee.springConstant * deltaL;

					if (bungee.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
					{
						bungee.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					}

					if (bungee.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
					{
						bungee.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
					}


					getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position,
						deltaL >= 0 ? Color::Red : Color::Green);
				}
			}
		}
	}
}
