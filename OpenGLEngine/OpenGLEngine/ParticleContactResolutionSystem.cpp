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
	float ParticleContactResolutionSystem::CalculateSeparationVelocity(ParticleContactEvent & contact)
	{
		Vector3 velocityA = contact.entityA.hasComponent<ParticleComponent>() ? 
			contact.entityA.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);
		Vector3 velocityB = contact.entityB.hasComponent<ParticleComponent>() ?
			contact.entityB.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);
		Vector3 seperationVelocity = velocityA - velocityB;
		return glm::dot(seperationVelocity, contact.normal);
	}
	void ParticleContactResolutionSystem::ResolveVelocity(ParticleContactEvent & contact, float deltaTime)
	{
		float seperationVel = CalculateSeparationVelocity(contact);

		if (seperationVel > 0)
		{
			return;
		}

		float newSeperationVel = -seperationVel * contact.restitution;
		float deltaVel = newSeperationVel - seperationVel;

		float inverseMassA = contact.entityA.hasComponent<ForceAccumulatorComponent>() ?
			contact.entityA.getComponent<ForceAccumulatorComponent>().inverseMass : 0.0f;
		float inverseMassB = contact.entityB.hasComponent<ForceAccumulatorComponent>() ?
			contact.entityB.getComponent<ForceAccumulatorComponent>().inverseMass : 0.0f;
		float totalInverseMass = inverseMassA + inverseMassB;
		if (totalInverseMass <= 0) { return; }
		
		float impulse = deltaVel / totalInverseMass;
		Vector3 impulsePerIMass = contact.normal * impulse;
		if (contact.entityA.hasComponent<ParticleComponent>())
		{
			contact.entityA.getComponent<ParticleComponent>().velocity += impulsePerIMass * inverseMassA;
		}
		if (contact.entityB.hasComponent<ParticleComponent>())
		{
			contact.entityB.getComponent<ParticleComponent>().velocity += impulsePerIMass * inverseMassB;
		}

	}
}
