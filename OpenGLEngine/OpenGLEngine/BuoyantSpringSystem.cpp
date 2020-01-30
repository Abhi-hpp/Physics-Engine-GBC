#include "BuoyantSpringSystem.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"
#include "BuoyantSpringComponent.h"

#include "ParticleComponent.h"

namespace Reality
{
	BuoyantSpringSystem::BuoyantSpringSystem()
	{
		requireComponent<BuoyantSpringComponent>();
	}

	void BuoyantSpringSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& springTransform = e.getComponent<TransformComponent>();
			auto& spring = e.getComponent<BuoyantSpringComponent>();

			if (spring.connectedEntityA.hasComponent<TransformComponent>()
				&& spring.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = spring.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = spring.connectedEntityB.getComponent<TransformComponent>();

				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);
				BuoyantSpringComponent water();

				if (length > 0)
				{
					float deltaL = length - spring.restLength;
					Vector3 force = -glm::normalize(relativePosition);
					force *= spring.springConstant * deltaL;
					//forceAcc.AddForce(force);


					// Code Here:
					if (transformA.position.y > 0.0f)
					{
						spring.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					}
					else if (transformA.position.y <= 0.0f)
					{
						spring.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					}

					float g = 1.0f / (1.0f + pow(abs(deltaL), 0.5f));

					float r = 1 - g;

					Color col = Color(r, g, 0, 1);

					float deltaLength = length / 10.0f;
					Vector3 direction = -glm::normalize(relativePosition);
					for (int i = 0; i < 10; i++)
					{
						getWorld().data.renderUtil->DrawCube(
							transformA.position + (float)i * deltaLength * direction,
							Vector3(1.0f, 1.0f, 1.0f) * min((spring.restLength / 20.0f), 100.0f), Vector3(0, 0, 0), col);
					}

					getWorld().data.renderUtil->DrawLine(springTransform.position, transformA.position, col);
				}
			}
		}
	}
}
