#include "NBodySystem.h"
#include "ForceAccumulatorComponent.h"
#include "ParticleComponent.h"
#include "GravityForceComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<NBodyComponent>();
		requireComponent<TransformComponent>();
		requireComponent<ParticleComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e1 : getEntities())
		{
			for (auto e2 : getEntities())
			{
				// object1
				auto& e1NBody = e1.getComponent<NBodyComponent>();
				auto& e1Transform = e1.getComponent<TransformComponent>();
				auto& e1ForceAcc = e1.getComponent<ForceAccumulatorComponent>();

				// object2
				auto& e2NBody = e2.getComponent<NBodyComponent>();
				auto& e2Transform = e2.getComponent<TransformComponent>();
				auto& e2ForceAcc = e2.getComponent<ForceAccumulatorComponent>();

				if (e1Transform.position != e2Transform.position)
				{
					Vector3 relativePosition = e1Transform.position - e2Transform.position;
					Vector3 direction = glm::normalize(relativePosition);
					float distance = glm::length(relativePosition);

					// F = g * (m1*m2)/r^2
					float force = e1NBody.g * ((e1NBody.mass * e2NBody.mass) / (distance * distance));

					// Add forces to attract objects.
					if (force >= e1NBody.maxSpeed)
					{
						e1ForceAcc.AddForce(e1NBody.maxSpeed * -direction);
						e2ForceAcc.AddForce(e1NBody.maxSpeed * direction);
					}
					else 
					{
						e1ForceAcc.AddForce(force * -direction);
						e2ForceAcc.AddForce(force * direction);
					}
				}
			}
		}
	}
}