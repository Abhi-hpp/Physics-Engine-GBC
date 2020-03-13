#include "NBodySystem.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<NBodyComponent>();
		requireComponent<TransformComponent>();
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& entities = e.getComponent<NBodyComponent>().entities;
			auto& nBody = e.getComponent<NBodyComponent>();

			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 10; j++)
				{
					if (i != j)
					{
						float distance = glm::distance(entities[i].getComponent<TransformComponent>().position, entities[j].getComponent<TransformComponent>().position);
						float force = (nBody.gravity * nBody.mass * entities[j].getComponent<NBodyComponent>().mass) / pow(distance, 2);
						Vector3 direction = entities[j].getComponent<TransformComponent>().position - entities[i].getComponent<TransformComponent>().position;
					
						entities[i].getComponent<ForceAccumulatorComponent>().AddForce(force * direction);
					}
				}
			}
		}
	}
}
