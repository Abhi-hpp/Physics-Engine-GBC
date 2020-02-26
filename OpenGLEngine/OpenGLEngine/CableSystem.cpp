#include "CableSystem.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	CableSystem::CableSystem()
	{
		requireComponent<CableComponent>();
	}

	void CableSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& cable = e.getComponent<CableComponent>();

			if (cable.entityA.hasComponent<TransformComponent>() &&
				cable.entityB.hasComponent<TransformComponent>())
			{
				auto& transformA = cable.entityA.getComponent<TransformComponent>();
				auto& transformB = cable.entityB.getComponent<TransformComponent>();

				Vector3 relativePos = transformA.position - transformB.position;
				float length = glm::length(relativePos);

				if (length > cable.maxLength)
				{
					Vector3 normal = -glm::normalize(relativePos);
					float penetration = length - cable.maxLength;

					getWorld().getEventManager().emitEvent<ParticleContactEvent>(
						cable.entityA,
						cable.entityB,
						cable.restitution,
						normal,
						penetration
						);
				}

				getWorld().data.renderUtil->DrawLine(
					transformA.position,
					transformB.position,
					Color::Magenta
				);
			}
		}
	}
}
