#include "BridgeRopeSystem.h"
#include "TransformComponent.h"
#include "ParticleCollideCheck.h"

namespace Reality
{
	BridgeRopeSystem::BridgeRopeSystem()
	{
		requireComponent<BridgeRopeComponent>();
	}

	void BridgeRopeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& rope = e.getComponent<BridgeRopeComponent>();

			if (rope.entityA.hasComponent<TransformComponent>() &&	rope.entityB.hasComponent<TransformComponent>())
			{
				//Cable A
				auto& transformA = rope.entityA.getComponent<TransformComponent>();
				//Cable B
				auto& transformB = rope.entityB.getComponent<TransformComponent>();

				
				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);

				if (length > rope.maximumLength)
				{
					Vector3 normal = -glm::normalize(relativePosition);

					float penetration = length - rope.maximumLength;

					getWorld().getEventManager().emitEvent<ParticleCollideCheck>(rope.entityA,	rope.entityB, rope.restitution, normal, penetration );
				}

				getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position, Color::Magenta );
			}
		}
	}
}
