#include "NBodySystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<NBodyComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (int i = 0; i < getEntities().size(); i++)
		{
			for (int j = i + 1; j < getEntities().size(); j++)
			{
				Vector3 vectorBetweenParticles = Vector3(getEntities()[i].getComponent<TransformComponent>().position - getEntities()[j].getComponent<TransformComponent>().position);
				float distance = glm::length(vectorBetweenParticles);
				// F = G * m1m2 / r^2
				float gravity = 9.8 * ((getEntities()[i].getComponent<NBodyComponent>().mass) * (getEntities()[j].getComponent<NBodyComponent>().mass)) / (distance * distance);
				// Calculate and add force
				Vector3 Force = vectorBetweenParticles * gravity;
				getEntities()[j].getComponent<ForceAccumulatorComponent>().AddForce(Force);
			}
		}

		for (auto e : getEntities())
		{
			getWorld().data.renderUtil->DrawSphere(e.getComponent<TransformComponent>().position, 1.0f, Color::White);
		}
	}
}
