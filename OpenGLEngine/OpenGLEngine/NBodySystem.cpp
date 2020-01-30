#include "NBodySystem.h"
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
		for (auto e : getEntities())
		{
			auto& entity1Transform = e.getComponent<TransformComponent>();
			auto& entity1NBody = e.getComponent<NBodyComponent>();
			auto& entity1ForceAcc = e.getComponent<ForceAccumulatorComponent>();

			for (auto e2 : getEntities())
			{
				auto& entity2Transform = e2.getComponent<TransformComponent>();
				auto& entity2NBody = e2.getComponent<NBodyComponent>();
				auto& entity2ForceAcc = e2.getComponent<ForceAccumulatorComponent>();

				if (e != e2)
				{
					Vector3 relativeVec = entity1Transform.position - entity2Transform.position;
					float dis = glm::length(relativeVec);

					if (dis > 0)
					{
						float force = G * entity1NBody.mass * entity2NBody.mass / (dis * dis);
						Vector3 forceDir = glm::normalize(relativeVec);
						
						if (force > 100)
							force = 100;

						entity1ForceAcc.AddForce(force * -forceDir);
						entity2ForceAcc.AddForce(force * forceDir);
					}
				}
			}
		}
	}
}
