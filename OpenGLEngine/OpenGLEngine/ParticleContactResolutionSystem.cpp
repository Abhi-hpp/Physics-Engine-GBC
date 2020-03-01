#include "ParticleContactResolutionSystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorSystem.h"
#include "TransformComponent.h"
#include "PenetrationDeltaMoveComponent.h"

namespace Reality
{
	ParticleContactResolutionSystem::ParticleContactResolutionSystem()
	{

	}

	void ParticleContactResolutionSystem::Update(float deltaTime)
	{
		auto contactEvents = getWorld().getEventManager().getEvents<ParticleContactEvent>();
		if (contactEvents.size() > 0)
		{
			for (int i = 0; i < velocityIterations; i++)
			{
				// Sort from highest incoming OR most negetive separting velocity to least
				std::sort(contactEvents.begin(), contactEvents.end(), 
					[this](auto a, auto b)
					{
						return CalculateSeparationVelocity(a) < CalculateSeparationVelocity(b);
					});
				ResolveVelocity(contactEvents[0], deltaTime);
			}
			for (int i = 0; i < positionIterations; i++)
			{
				// Sort from highest penetration to the least
				std::sort(contactEvents.begin(), contactEvents.end(),
					[this](auto a, auto b)
					{
						return CalculateActualPenetration(a) > CalculateActualPenetration(b);
					});
				ResolveInterPenetration(contactEvents[0]);
			}
		}
		//for (auto& contact : contactEvents)
		//{
		//	ResolveVelocity(contact, deltaTime);
		//	ResolveInterPenetration(contact);
		//}
	}

	float ParticleContactResolutionSystem::CalculateSeparationVelocity(ParticleContactEvent & contact)
	{
		Vector3 velocityA = contact.entityA.hasComponent<ParticleComponent>() ?
			contact.entityA.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);

		Vector3 velocityB = contact.entityB.hasComponent<ParticleComponent>() ?
			contact.entityB.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);

		Vector3 separationVelocity = velocityA - velocityB;

		return glm::dot(separationVelocity, contact.normal);
	}

	float ParticleContactResolutionSystem::CalculateActualPenetration(ParticleContactEvent & contact)
	{
		float actualPenetration = contact.penetration;

		if (contact.entityA.hasComponent<PenetrationDeltaMoveComponent>())
		{
			Vector3 deltaMove = contact.entityA.getComponent<PenetrationDeltaMoveComponent>().deltaMove;
			actualPenetration -= glm::dot(deltaMove, contact.normal);
		}

		if (contact.entityB.hasComponent<PenetrationDeltaMoveComponent>())
		{
			Vector3 deltaMove = contact.entityB.getComponent<PenetrationDeltaMoveComponent>().deltaMove;
			actualPenetration += glm::dot(deltaMove, contact.normal);
		}

		return actualPenetration;
	}

	void ParticleContactResolutionSystem::ResolveVelocity(ParticleContactEvent & contact, float deltaTime)
	{
		float initialVelocity = CalculateSeparationVelocity(contact);

		if (initialVelocity > 0)
		{
			return;
		}

		float finalVelocity = -initialVelocity * contact.restitution;

		Vector3 relativeAccelaration = Vector3(0, 0, 0);
		if (contact.entityA.hasComponent<ParticleComponent>())
		{
			relativeAccelaration += contact.entityA.getComponent<ParticleComponent>().acceleration;
		}
		if (contact.entityB.hasComponent<ParticleComponent>())
		{
			relativeAccelaration -= contact.entityB.getComponent<ParticleComponent>().acceleration;
		}

		float accCausedSepVelocity = glm::dot(relativeAccelaration, contact.normal) * deltaTime;

		if (accCausedSepVelocity < 0)
		{
			finalVelocity += contact.restitution * accCausedSepVelocity;

			if (finalVelocity < 0)
			{
				finalVelocity = 0;
			}
		}

		float deltaVelocity = finalVelocity - initialVelocity;

		float invMA = contact.entityA.hasComponent<ForceAccumulatorComponent>() ?
			contact.entityA.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float invMB = contact.entityB.hasComponent<ForceAccumulatorComponent>() ?
			contact.entityB.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float totalInverseMass = invMA + invMB;

		if (totalInverseMass <= 0)
		{
			return;
		}

		float impulse = deltaVelocity / totalInverseMass;
		Vector3 impulsePerIMass = impulse * contact.normal;

		if (contact.entityA.hasComponent<ParticleComponent>())
		{
			contact.entityA.getComponent<ParticleComponent>().velocity += impulsePerIMass * invMA;
		}

		if (contact.entityB.hasComponent<ParticleComponent>())
		{
			contact.entityB.getComponent<ParticleComponent>().velocity -= impulsePerIMass * invMB;
		}
	}
	void ParticleContactResolutionSystem::ResolveInterPenetration(ParticleContactEvent & contact)
	{
		float actualPenetration = CalculateActualPenetration(contact);

		if (actualPenetration < 0)
		{
			return;
		}

		float invMassA = contact.entityA.hasComponent<ForceAccumulatorComponent>() ?
			contact.entityA.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float invMassB = contact.entityB.hasComponent<ForceAccumulatorComponent>() ?
			contact.entityB.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float totalInverseMass = invMassA + invMassB;

		if (totalInverseMass <= 0)
		{
			return;
		}

		Vector3 movePerUnitIMass = contact.normal * (actualPenetration / totalInverseMass);

		if (contact.entityA.hasComponent<TransformComponent>())
		{
			Vector3 deltaMove = movePerUnitIMass * invMassA;
			contact.entityA.getComponent<TransformComponent>().position += deltaMove;
			if (contact.entityA.hasComponent<PenetrationDeltaMoveComponent>())
			{
				contact.entityA.getComponent<PenetrationDeltaMoveComponent>().deltaMove += deltaMove;
			}
		}

		if (contact.entityB.hasComponent<TransformComponent>())
		{
			Vector3 deltaMove = movePerUnitIMass * invMassB;
			contact.entityB.getComponent<TransformComponent>().position -= movePerUnitIMass * invMassB;
			if (contact.entityB.hasComponent<PenetrationDeltaMoveComponent>())
			{
				contact.entityB.getComponent<PenetrationDeltaMoveComponent>().deltaMove -= deltaMove;
			}
		}

	}
}
