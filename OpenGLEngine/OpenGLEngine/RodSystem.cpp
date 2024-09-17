#include "RodSystem.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	RodSystem::RodSystem()
	{
		requireComponent<RodComponent>();
	}

	void RodSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& rod = e.getComponent<RodComponent>();

			if (rod.entityA.hasComponent<TransformComponent>() &&
				rod.entityB.hasComponent<TransformComponent>())
			{
				auto& transformA = rod.entityA.getComponent<TransformComponent>();
				auto& transformB = rod.entityB.getComponent<TransformComponent>();

				Vector3 relativePos = transformA.position - transformB.position;
				float length = glm::length(relativePos);

				if (length > rod.rodLength)
				{
					Vector3 normal = -glm::normalize(relativePos);
					float penetration = length - rod.rodLength;

					getWorld().getEventManager().emitEvent<ParticleContactEvent>(
						rod.entityA,
						rod.entityB,
						0,
						normal,
						penetration
						);
				}

				if (length < rod.rodLength)
				{
					Vector3 normal = glm::normalize(relativePos);
					float penetration = rod.rodLength - length;

					getWorld().getEventManager().emitEvent<ParticleContactEvent>(
						rod.entityA,
						rod.entityB,
						0,
						normal,
						penetration
						);
				}

				getWorld().data.renderUtil->DrawLine(
					transformA.position,
					transformB.position,
					Color::Beige
				);
			}
		}
	}
}
