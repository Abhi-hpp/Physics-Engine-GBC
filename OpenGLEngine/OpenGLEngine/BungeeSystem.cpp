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
				
				Vector3 force; 
				//Vector3 relativePosition.force;
				force -= springTransform.position;
				
				float length = glm::length(relativePosition);
				float deltaL = length - spring.restLength;
				
				// Check if the bungee is compressed
				if (deltaL <= spring.restLength)
				{
					
					Vector3 force = -glm::normalize(relativePosition);
			
					force *= -deltaL;
					forceAcc.AddForce(force);
					//force *= spring.bungeeConstant * deltaL;
					//forceAcc.AddForce(force);

					float g = 1.0f / (1.0f + pow(abs(deltaL), 0.5f));
					float r = 1 - g;

					Color col = Color(r, g, 0, 1);

					Vector3 direction = -glm::normalize(relativePosition);
					for (int i = 0; i < 10; i++)
					{
						getWorld().data.renderUtil->DrawCube(
							transform.position + (float)i * deltaL * direction,
							Vector3(1.0f, 1.0f, 1.0f) * min((spring.restLength / 20.0f), 100.0f), Vector3(0, 0, 0), col);

					}
					getWorld().data.renderUtil->DrawLine(springTransform.position, transform.position,
						col);
				}

					// Calculate the magnitude of the force.
					deltaL = spring.bungeeConstant * (spring.restLength - deltaL);

					// Calculate the final force and apply it.
}				
					


		}
	}
}
