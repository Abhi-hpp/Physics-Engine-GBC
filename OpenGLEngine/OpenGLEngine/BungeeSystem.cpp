#include "BungeeSystem.h"
#include "ForceAccumulatorComponent.h"
namespace Reality
{
	BungeeSystem::BungeeSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BungeeComponent>();
	}

	void BungeeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& springTransform = e.getComponent<TransformComponent>();
			auto& spring = e.getComponent<BungeeComponent>();

			if (spring.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& spring.connectedEntity.hasComponent<TransformComponent>())
			{
				auto& forceAcc = spring.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto& transform = spring.connectedEntity.getComponent<TransformComponent>();

				// Calculate the vector of the spring.
				Vector3 relativePosition = transform.position - springTransform.position;
				
				float length = glm::length(relativePosition);
				float deltaL = length - spring.restLength;
				// Check if the bungee is compressed
				if (deltaL <= spring.restLength)
				{
					
					Vector3 force = -glm::normalize(relativePosition);
					force *= spring.bungeeConstant * deltaL;
					forceAcc.AddForce(force);





				}

			}


		}
	}
}
