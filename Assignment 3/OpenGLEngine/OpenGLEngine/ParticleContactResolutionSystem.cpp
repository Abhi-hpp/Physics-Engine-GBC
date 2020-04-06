#include "ParticleContactResolutionSystem.h"
#include "ParticleComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	ParticleContactResolutionSystem::ParticleContactResolutionSystem()
	{
		requireComponent<ParticleContactComponent>();
	}

	float ParticleContactResolutionSystem::CalculateSeparatingVelocity(ParticleContactComponent& contact)
	{
		Vector3 velocityA = contact.entityA.hasComponent<ParticleComponent>() ? contact.entityA.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);
		Vector3 velocityB = contact.entityB.hasComponent<ParticleComponent>() ? contact.entityB.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);
		Vector3 relativeVel = velocityA - velocityB;
		return glm::dot(relativeVel, contact.normal);
	}

	void ParticleContactResolutionSystem::ResolveVelocity(ParticleContactComponent& contact, float deltaTime)
	{
		float separatingVelocity = CalculateSeparatingVelocity(contact);

		if (separatingVelocity > 0)
		{
			return;
		}

		bool isAvalid = contact.entityA.hasComponent<ParticleComponent>();
		bool isBvalid = contact.entityB.hasComponent<ParticleComponent>();
		float invM1 = isAvalid ? contact.entityA.getComponent<ParticleComponent>().inverseMass : 0;
		float invM2 = isBvalid ? contact.entityB.getComponent<ParticleComponent>().inverseMass : 0;


		float newSeparatingVelocity = -separatingVelocity * contact.restitution;

		// Check the velocity build up due to accelaration only
		Vector3 accCausedVelocity = Vector3(0, 0, 0);
		if (isAvalid)
		{
			accCausedVelocity += contact.entityA.getComponent<ParticleComponent>().accelaration;
		}
		if (isBvalid)
		{
			accCausedVelocity -= contact.entityB.getComponent<ParticleComponent>().accelaration;
		}
		float accCausedSepVelocity = glm::dot(accCausedVelocity, contact.normal) * deltaTime;

		// If we have a closing velocity due to accelaration build up, 
		// remove it from new separating velocity
		if (accCausedSepVelocity < 0)
		{
			newSeparatingVelocity += contact.restitution * accCausedSepVelocity;
			if (newSeparatingVelocity < 0)
			{
				newSeparatingVelocity = 0;
			}
		}

		float deltaVelocity = newSeparatingVelocity - separatingVelocity;

		float totalInverseMass = invM1 + invM2;

		if (totalInverseMass <= 0)
		{
			return;
		}

		float impulse = deltaVelocity / totalInverseMass;

		Vector3 impulsePerIMass = contact.normal * impulse;

		if (isAvalid)
		{
			contact.entityA.getComponent<ParticleComponent>().velocity += impulsePerIMass * invM1;
		}
		if (isBvalid)
		{
			contact.entityB.getComponent<ParticleComponent>().velocity -= impulsePerIMass * invM2;
		}
	}

	void ParticleContactResolutionSystem::ResolveInterpenetration(ParticleContactComponent& contact)
	{
		if (contact.penetration <= 0)
		{
			return;
		}

 		bool isAvalid = contact.entityA.hasComponent<ParticleComponent>();
		bool isBvalid = contact.entityB.hasComponent<ParticleComponent>();
		float invM1 = isAvalid ? contact.entityA.getComponent<ParticleComponent>().inverseMass : 0;
		float invM2 = isBvalid ? contact.entityB.getComponent<ParticleComponent>().inverseMass : 0;

		float totalInverseMass = invM1 + invM2;

		if (totalInverseMass <= 0)
		{
			return;
		}

		Vector3 movePerMass = contact.normal * (-contact.penetration / totalInverseMass);
		contact.deltaMovePerMass = movePerMass;
		if (isAvalid)
		{
			contact.entityA.getComponent<TransformComponent>().position -= movePerMass * invM1;
		}

		if (isBvalid)
		{
			contact.entityB.getComponent<TransformComponent>().position += movePerMass * invM2;
		}
		//contact.penetration = 0;
	}

	void ParticleContactResolutionSystem::UpdateInterpenetration(ParticleContactComponent & bestContact, ParticleContactComponent & contact)
	{
		bool isAvalid = contact.entityA.hasComponent<ParticleComponent>();
		bool isBvalid = contact.entityB.hasComponent<ParticleComponent>();
		float invM1 = isAvalid ? contact.entityA.getComponent<ParticleComponent>().inverseMass : 0;
		float invM2 = isBvalid ? contact.entityB.getComponent<ParticleComponent>().inverseMass : 0;
		if (bestContact.entityA == contact.entityA || bestContact.entityB == contact.entityA)
		{
			float mult = bestContact.entityA == contact.entityA ? -1 : 1;
			Vector3 deltaMove = mult * bestContact.deltaMovePerMass * invM1;
			float deltaPenetration = glm::dot(deltaMove, contact.normal);
			contact.penetration -= deltaPenetration;
		}
		if (bestContact.entityB == contact.entityB || bestContact.entityA == contact.entityB)
		{
			float mult = bestContact.entityA == contact.entityB ? -1 : 1;
			Vector3 deltaMove = mult * bestContact.deltaMovePerMass * invM2;
			float deltaPenetration = glm::dot(deltaMove, contact.normal);
			contact.penetration += deltaPenetration;
		}
	}

	void ParticleContactResolutionSystem::Update(float deltaTime)
	{
		iterationsUsed = 0;
		iterations = getEntities().size() * 2;

		if (getEntities().size() > 0)
		{
			unsigned int bestContactIndex = 0;
			unsigned int lastBest = 0;
			while (iterationsUsed < iterations)
			{
				// Find the contact with the largest closing velocity
				float max = 0;
				for (int i = 0; i < getEntities().size(); i++)
				{
					auto e = getEntities()[i];
					auto &contact = e.getComponent<ParticleContactComponent>();
					if (iterationsUsed > 0)
					{
						UpdateInterpenetration(getEntities()[lastBest].getComponent<ParticleContactComponent>(), contact);
					}
					float sepVel = CalculateSeparatingVelocity(contact);
					if (sepVel < max)
					{
						max = sepVel;
						bestContactIndex = i;
					}
				}
				if (max >= 0)
				{
					break;
				}
				auto& bestContact = getEntities()[bestContactIndex].getComponent<ParticleContactComponent>();
				ResolveVelocity(bestContact, deltaTime);
				ResolveInterpenetration(bestContact);
				lastBest = bestContactIndex;
				iterationsUsed++;
			}

			for (auto e : getEntities())
			{
				e.kill();
			}
		}



	}
}
