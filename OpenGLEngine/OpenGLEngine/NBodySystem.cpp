#include "NBodySystem.h"
#include "TransformComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<ForceAccumulatorComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& particleTransform = e.getComponent<TransformComponent>();
			auto& particleForceAcc = e.getComponent<ForceAccumulatorComponent>();

			// Calculate the force of gravity
			float force =
				gravityConstant * ((mass*(1 / particleForceAcc.inverseMass)) /
				pow(glm::length(particleTransform.position - centerPoint), 2));

			particleForceAcc.AddForce((glm::normalize(centerPoint - particleTransform.position)
				*force));
		}

		// Gravitational force pulls all particles towards each other, as well as the "sun"
		if (getEntities().size() > 1)
		{
			for (int i = 0; i < getEntities().size() - 1; i++) {
				for (int j = i + 1; j < getEntities().size() - 1; j++) {
					auto& particle1Transform = getEntities()[i].getComponent<TransformComponent>();
					auto& particle1ForceAcc = getEntities()[i].getComponent<ForceAccumulatorComponent>();
					auto& particle2Transform = getEntities()[j].getComponent<TransformComponent>();
					auto& particle2ForceAcc = getEntities()[j].getComponent<ForceAccumulatorComponent>();

					float force =
						gravityConstant * (((1 / particle1ForceAcc.inverseMass)*(1 / particle2ForceAcc.inverseMass)) /
							pow(glm::length(particle1Transform.position - particle2Transform.position), 2));

					particle1ForceAcc.AddForce((glm::normalize(particle2Transform.position - particle1Transform.position)
						*force));
					particle2ForceAcc.AddForce((glm::normalize(particle1Transform.position - particle2Transform.position)
						*force));
				}
			}
		}
		// Draw "sun"
		for (auto e : getEntities()) 
		{
			if (e.hasComponent<NBodyComponent>()) {
				getWorld().data.renderUtil->DrawSphere(centerPoint, 3, Color(1, 1, 1, 1));
			}
		}
	}
}
