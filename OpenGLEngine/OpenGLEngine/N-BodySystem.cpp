#include "N-BodySystem.h"

namespace Reality
{
	N_BodySystem::N_BodySystem()
	{
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<N_BodyComponent>();
		requireComponent<TransformComponent>();
	}

	void N_BodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			// Get every other enitiy 
			for (auto enities : getEntities())
			{
				if (e == enities)
				{
					continue; // The enity should not count its own force
				}

				auto& transform1 = e.getComponent<TransformComponent>();
				auto& forceAcc1 = e.getComponent<ForceAccumulatorComponent>();

				auto& transform2 = enities.getComponent<TransformComponent>();
				auto& forceAcc2 = enities.getComponent<ForceAccumulatorComponent>();

				// Find the distance between the two enities
				Vector3 distance = transform2.position - transform1.position;

				// Now find the length 
				float length = glm::length(distance);

				// Create a force vector that first has the direction of the force
				Vector3 force = glm::normalize(distance);

				float gravity = 300.0f; // TEMP VALUE FOR GRAVITY CONSTANT
				
				force *= gravity * ((forceAcc1.inverseMass * forceAcc2.inverseMass) / length * length);

				forceAcc1.AddForce(force);
			}
		}
	}
}
