#include "BungeeChordSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"
#include "SpawnBungeeEvent.h"

namespace Reality
{
	BungeeChordSystem::BungeeChordSystem()
	{
		requireComponent<BungeeChordComponent>();
	}

	void BungeeChordSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& bungee = e.getComponent<BungeeChordComponent>();

			if (bungee.connectedEntityA.hasComponent<TransformComponent>() &&
				bungee.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = bungee.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = bungee.connectedEntityB.getComponent<TransformComponent>();

				Vector3 relativePos = transformA.position - transformB.position;
				float length = glm::length(relativePos);

				if (length > bungee.restLength)
				{
					float deltaL = length - bungee.restLength;
					Vector3 force = -glm::normalize(relativePos);
					force *= bungee.springConstant * deltaL;

					if (bungee.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
						bungee.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					if (bungee.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
						bungee.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);

					getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position, deltaL > 0 ? Color::Red : Color::Blue);
				}
			}
		}
	}
}
