#include "ParticleContactResolutionSystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	ParticleContactResolutionSystem::ParticleContactResolutionSystem()
	{

	}

	void ParticleContactResolutionSystem::Update(float deltaTime)
	{
		auto contactEvents = getWorld().getEventManager().getEvents<ParticleContactEvent>();
		for (auto& contact : contactEvents)
		{
			ResolveVelocity(contact, deltaTime);
		}
	}

	float ParticleContactResolutionSystem::CalculateSeparatingVelocity(ParticleContactEvent & contact)
	{
		Vector3 velocityA = contact.entityA.hasComponent<ParticleComponent>() ? contact.entityA.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);
		Vector3 velocityB = contact.entityB.hasComponent<ParticleComponent>() ? contact.entityB.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);

		Vector3 relativeVelocity = velocityA - velocityB;

		return glm::dot(relativeVelocity, contact.normal);
	}
	
	void ParticleContactResolutionSystem::ResolveVelocity(ParticleContactEvent & contact, float deltaTime)
	{
		float initialSeparatingVelocity = CalculateSeparatingVelocity(contact);

		if (initialSeparatingVelocity >= 0)
		{
			return;
		}

		float finalSeparatingVelocity = -contact.restitution * initialSeparatingVelocity;
		float deltaVelocity = finalSeparatingVelocity - initialSeparatingVelocity;

		float inverseMassA = contact.entityA.hasComponent<ForceAccumulatorComponent>() ? contact.entityA.getComponent<ForceAccumulatorComponent>().inverseMass : 0;
		float inverseMassB = contact.entityB.hasComponent<ForceAccumulatorComponent>() ? contact.entityB.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float totalInverseMass = inverseMassA + inverseMassB;

		if (totalInverseMass <= 0)
		{
			return;
		}

		float impulse = deltaVelocity / totalInverseMass;
		Vector3 impulsePerIMass = impulse * contact.normal;

		if (contact.entityA.hasComponent<ParticleComponent>())
		{
			contact.entityA.getComponent<ParticleComponent>().velocity += impulsePerIMass * inverseMassA;
		}
		if (contact.entityB.hasComponent<ParticleComponent>())
		{
			contact.entityB.getComponent<ParticleComponent>().velocity -= impulsePerIMass * inverseMassB;
		}
	}
}
