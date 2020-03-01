#include "BridgeRodSystem.h"
#include "TransformComponent.h"
#include "ParticleCollideCheck.h"

namespace Reality
{
	BridgeRodSystem::BridgeRodSystem()
	{
		requireComponent<BridgeRodComponent>();
	}

	void BridgeRodSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& rod = e.getComponent<BridgeRodComponent>();

			if (rod.entityA.hasComponent<TransformComponent>() && rod.entityB.hasComponent<TransformComponent>())
			{
				//Rod A
				auto& transformA = rod.entityA.getComponent<TransformComponent>();

				//Rod B
				auto& transformB = rod.entityB.getComponent<TransformComponent>();

				Vector3 relativePos = transformA.position - transformB.position;
				float length = glm::length(relativePos);

				if (length > rod.rodMaxLength)
				{
					Vector3 normal = -glm::normalize(relativePos);
					float penetration = length - rod.rodMaxLength;

					getWorld().getEventManager().emitEvent<ParticleCollideCheck>(rod.entityA, rod.entityB, 0, normal, penetration );
				}

				if (length < rod.rodMaxLength)
				{
					Vector3 normal = glm::normalize(relativePos);
					float penetration = rod.rodMaxLength - length;

					getWorld().getEventManager().emitEvent<ParticleCollideCheck>(rod.entityA, rod.entityB, 0, normal, penetration );
				}

				getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position, Color::Red );
			}
		}
	}
}
