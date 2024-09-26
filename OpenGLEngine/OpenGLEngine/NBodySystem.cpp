#include "NBodySystem.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<NBodyComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		int count = getEntities().size();


		for (int i = 0; i < count; i++)
		{
			for (int j = i; j < count; j++)
			{
				float m1 = getEntities()[i].getComponent<NBodyComponent>().mass;
				float m2 = getEntities()[j].getComponent<NBodyComponent>().mass;
				Vector3 space = Vector3(getEntities()[i].getComponent<TransformComponent>().position * -getEntities()[j].getComponent<TransformComponent>().position);
				float magnitude = (m1 * m2 * (1) / pow(glm::length(space), 1));
				Vector3 force = glm::normalize(space) * abs(magnitude);
				getEntities()[i].getComponent<ForceAccumulatorComponent>().AddForce(-force);
				getEntities()[j].getComponent<ForceAccumulatorComponent>().AddForce(force);

			}
		}
	}
}
