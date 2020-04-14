#include "PairedSpringForceGeneratorSystem.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"

namespace Reality
{
	PairedSpringForceGeneratorSystem::PairedSpringForceGeneratorSystem()
	{
		requireComponent<PairedSpringComponent>();
	}


	void PairedSpringForceGeneratorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &spring = e.getComponent<PairedSpringComponent>();

			if (spring.entityA.hasComponent<TransformComponent>() &&
				spring.entityB.hasComponent<TransformComponent>())
			{
				//auto &particle = spring.entity.getComponent<ParticleComponent>();
				auto &entityTransformA = spring.entityA.getComponent<TransformComponent>();
				auto &entityTransformB = spring.entityB.getComponent<TransformComponent>();

				Vector3 relativePosition = entityTransformA.position - entityTransformB.position;
				float length = glm::length(relativePosition);
				float x = length - spring.restLength;
				Vector3 direction = glm::normalize(relativePosition);

				if (spring.entityA.hasComponent<ParticleComponent>())
				{
					spring.entityA.getComponent<ParticleComponent>().AddForce(-spring.springConstant * x * direction);
				}

				if (spring.entityB.hasComponent<ParticleComponent>())
				{
					spring.entityB.getComponent<ParticleComponent>().AddForce(spring.springConstant * x * direction);
				}

				float g = 1.0f / (1.0f + pow(abs(x), 0.5f));
				float r = (1 - g);
				Color color = Color(r, g, 0, 1);

				float deltaLength = length / 10.0f;
				for (int i = 0; i < 10; i++)
				{
					getWorld().data.renderUtil->DrawCube(
						entityTransformB.position + (float)i * deltaLength * direction,
						Vector3(0.1f, 0.1f, 0.1f) * min((spring.springConstant / 10.0f), 5.0f), Vector3(0,0,0), color);
				}

				getWorld().data.renderUtil->DrawLine(
					entityTransformB.position, entityTransformB.position + length * direction, color);
			}
		}

	}
}

