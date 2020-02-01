#include "BungeePairedSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BungeePairedSystem::BungeePairedSystem()
	{
		requireComponent<BungeePairedComponent>();
	}

	void BungeePairedSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& bungee = e.getComponent<BungeePairedComponent>();

			if (bungee.connectedEntityA.hasComponent<TransformComponent>()
				&& bungee.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = bungee.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = bungee.connectedEntityB.getComponent<TransformComponent>();
			
				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - bungee.restLength;
					Vector3 force = -glm::normalize(relativePosition);
					force *= bungee.springConstant * deltaL;

					if (length > bungee.restLength)
					{
						if (bungee.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
						{
							bungee.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
						}
						if (bungee.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
						{
							bungee.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
						}

						if (DEBUG_LOG_LEVEL > 0)
						{
							getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position, deltaL > 0 ? Color::Red : Color::Green);
						}
					}

				}

			}

		}
	}
}
