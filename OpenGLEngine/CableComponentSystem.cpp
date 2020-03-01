#include "CableComponentSystem.h"
#include "TransformComponent.h"
#include "ParticleContactComponent.h"

namespace Reality
{
	CableComponentSystem::CableComponentSystem()
	{
		requireComponent<CableComponent>();
	}

	void CableComponentSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& cable = e.getComponent<CableComponent>();
			float length = glm::length(cable.entityA.getComponent<TransformComponent>().position -
				cable.entityB.getComponent<TransformComponent>().position);
			
			getWorld().data.renderUtil->DrawSphere(cable.entityA.getComponent<TransformComponent>().position, 1, Color::Magenta);
			getWorld().data.renderUtil->DrawSphere(cable.entityB.getComponent<TransformComponent>().position, 1, Color::Magenta);

			getWorld().data.renderUtil->DrawLine(cable.entityA.getComponent<TransformComponent>().position,
				cable.entityB.getComponent<TransformComponent>().position, Color::Blue);

			if (length < cable.maxLength)
			{
				continue;
			}

			Vector3 normal = glm::normalize(cable.entityB.getComponent<TransformComponent>().position -
				cable.entityA.getComponent<TransformComponent>().position);

			float penetration = length - cable.maxLength;

			auto contactEntity = getWorld().createEntity();
			contactEntity.addComponent<ParticleContactComponent>(
				cable.entityA,
				cable.entityB,
				cable.restitution,
				normal,
				penetration);
		}
	}
}
