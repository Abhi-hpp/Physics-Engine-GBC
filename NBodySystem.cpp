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
				Vector3 dist = // distance of particles
					Vector3(getEntities()[i].getComponent<TransformComponent>().position - getEntities()[j].getComponent<TransformComponent>().position);
				float gravity = // gravity of particles
					9.8f * (getEntities()[i].getComponent<NBodyComponent>().mass * getEntities()[j].getComponent<NBodyComponent>().mass) /pow(glm::length(dist), 2);
				Vector3 F = // Force
					dist * gravity;
				getEntities()[j].getComponent<ForceAccumulatorComponent>().AddForce(F); // Push the particles
			}
		}

		for (auto e : getEntities())
		{
			getWorld().data.renderUtil->DrawSphere(e.getComponent<TransformComponent>().position, 1.0f, Color::Red);
		}
	}
}
