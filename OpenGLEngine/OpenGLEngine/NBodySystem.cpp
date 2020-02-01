#include "NBodySystem.h"

namespace Reality
{
	NBodySystem::NBodySystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<NBodyComponent>(); 
	}

	void NBodySystem::Update(float deltaTime)
	{
		for (auto a : getEntities())
		{
			auto& transformA = a.getComponent<TransformComponent>();
			auto& forceA = a.getComponent<ForceAccumulatorComponent>();
			auto& nBodyA = a.getComponent<NBodyComponent>();

			Vector3 force = Vector3(0,0,0); 
			
			for (auto b : getEntities())
			{
				if (a != b)
				{
					auto& transformB = b.getComponent<TransformComponent>();
					auto& forceB = a.getComponent<ForceAccumulatorComponent>();
					auto& nBodyB = b.getComponent<NBodyComponent>();

					float massA = 1/forceA.inverseMass; 
					float massB = 1/forceB.inverseMass;

					float distance = glm::distance(transformA.position, transformB.position);
					distance = max(5.0f, distance); 
					Vector3 direction = glm::normalize(transformB.position - transformA.position);
					force += (gravity) * (massA * massB / pow(distance, 2)) * direction;
				}
			}
			forceA.AddForce(force); 
		}
	}
}
