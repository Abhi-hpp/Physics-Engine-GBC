#include "ParticleCollisionResolvingSystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorSystem.h"
#include "TransformComponent.h"
#include "PenetrationMovementComponent.h"

namespace Reality
{
	ParticleCollisionResolvingSystem::ParticleCollisionResolvingSystem()
	{

	}

	void ParticleCollisionResolvingSystem::Update(float deltaTime)
	{
		auto collideEvents = getWorld().getEventManager().getEvents<ParticleCollideCheck>();

		if (collideEvents.size() > 0)
		{
			for (int i = 0; i < velocityIncrements; i++)
			{
				// Sort velocity in descending order.
				std::sort(collideEvents.begin(), collideEvents.end(), 
					[this](auto a, auto b)
					{
						return BounceOffVelocity(a) < BounceOffVelocity(b);
					});
				SolveVelocity(collideEvents[0], deltaTime);
			}
			for (int i = 0; i < positionIncrements; i++)
			{
				// Sort from highest penetration to the least
				std::sort(collideEvents.begin(), collideEvents.end(),
					[this](auto a, auto b)
					{
						return CheckPenetration(a) > CheckPenetration(b);
					});
				ResolveBounceOnPenetration(collideEvents[0]);
			}
		}
	
	}

	float ParticleCollisionResolvingSystem::BounceOffVelocity(ParticleCollideCheck& collide)
	{
		Vector3 velocityA = collide.entityA.hasComponent<ParticleComponent>() ?
			collide.entityA.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);

		Vector3 velocityB = collide.entityB.hasComponent<ParticleComponent>() ?
			collide.entityB.getComponent<ParticleComponent>().velocity : Vector3(0, 0, 0);

		Vector3 vBounceoffVelocity = velocityA - velocityB;

		return glm::dot(vBounceoffVelocity, collide.normal);
	}

	float ParticleCollisionResolvingSystem::CheckPenetration(ParticleCollideCheck& collide)
	{
		float penetrationCheck = collide.penetration;

		if (collide.entityA.hasComponent<PenetrationMovementComponent>())
		{
			Vector3 deltaMove = collide.entityA.getComponent<PenetrationMovementComponent>().deltaMove;
			penetrationCheck -= glm::dot(deltaMove, collide.normal);
		}

		if (collide.entityB.hasComponent<PenetrationMovementComponent>())
		{
			Vector3 deltaMove = collide.entityB.getComponent<PenetrationMovementComponent>().deltaMove;
			penetrationCheck += glm::dot(deltaMove, collide.normal);
		}

		return penetrationCheck;
	}

	void ParticleCollisionResolvingSystem::SolveVelocity(ParticleCollideCheck& collide, float deltaTime)
	{
		float initialVelocity = BounceOffVelocity(collide);

		if (initialVelocity > 0)
		{
			return;
		}

		float finalVelocity = -initialVelocity * collide.restitution;

		Vector3 relativeAccelaration = Vector3(0, 0, 0);
		if (collide.entityA.hasComponent<ParticleComponent>())
		{
			relativeAccelaration += collide.entityA.getComponent<ParticleComponent>().acceleration;
		}
		if (collide.entityB.hasComponent<ParticleComponent>())
		{
			relativeAccelaration -= collide.entityB.getComponent<ParticleComponent>().acceleration;
		}

		float SeperationVelocity = glm::dot(relativeAccelaration, collide.normal) * deltaTime;

		if (SeperationVelocity < 0)
		{
			finalVelocity += collide.restitution * SeperationVelocity;

			if (finalVelocity < 0)
			{
				finalVelocity = 0;
			}
		}

		float deltaVelocity = finalVelocity - initialVelocity;

		float inverseMassA = collide.entityA.hasComponent<ForceAccumulatorComponent>() ?
			collide.entityA.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float inverseMassB = collide.entityB.hasComponent<ForceAccumulatorComponent>() ?
			collide.entityB.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float totalInverseMass = inverseMassA + inverseMassB;

		if (totalInverseMass <= 0)
		{
			return;
		}

		float impulse = deltaVelocity / totalInverseMass;
		Vector3 impulsePerInversedMass = impulse * collide.normal;

		//to stabilize the bridge

		if (collide.entityA.hasComponent<ParticleComponent>())
		{
			collide.entityA.getComponent<ParticleComponent>().velocity += impulsePerInversedMass * inverseMassA;
		}

		if (collide.entityB.hasComponent<ParticleComponent>())
		{
			collide.entityB.getComponent<ParticleComponent>().velocity -= impulsePerInversedMass * inverseMassB;
		}
	}
	void ParticleCollisionResolvingSystem::ResolveBounceOnPenetration(ParticleCollideCheck& collide)
	{
		float penetrationCheck = CheckPenetration(collide);

		if (penetrationCheck < 0)
		{
			return;
		}
		// inverse masses for the entitities
		float inverseMassA = collide.entityA.hasComponent<ForceAccumulatorComponent>() ?
			collide.entityA.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float inverseMassB = collide.entityB.hasComponent<ForceAccumulatorComponent>() ?
			collide.entityB.getComponent<ForceAccumulatorComponent>().inverseMass : 0;

		float totalInverseMass = inverseMassA + inverseMassB;

		if (totalInverseMass <= 0)
		{
			return;
		}
		//set bounce movement.
		Vector3 movementPerUnitInverseMass = collide.normal * (penetrationCheck / totalInverseMass);

		if (collide.entityA.hasComponent<TransformComponent>())
		{
			Vector3 deltaMove = movementPerUnitInverseMass * inverseMassA;
			collide.entityA.getComponent<TransformComponent>().position += deltaMove;
			if (collide.entityA.hasComponent<PenetrationMovementComponent>())
			{
				collide.entityA.getComponent<PenetrationMovementComponent>().deltaMove += deltaMove;
			}
		}

		if (collide.entityB.hasComponent<TransformComponent>())
		{
			Vector3 deltaMove = movementPerUnitInverseMass * inverseMassB;
			collide.entityB.getComponent<TransformComponent>().position -= movementPerUnitInverseMass * inverseMassB;
			if (collide.entityB.hasComponent<PenetrationMovementComponent>())
			{
				collide.entityB.getComponent<PenetrationMovementComponent>().deltaMove -= deltaMove;
			}
		}

	}
}
