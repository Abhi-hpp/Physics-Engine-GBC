#include "FixedSpringForceGeneratorSystem.h"
#include "ParticleComponent.h"

namespace Reality
{
	FixedSpringForceGeneratorSystem::FixedSpringForceGeneratorSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<FixedSpringComponent>();
	}


	void FixedSpringForceGeneratorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &transform = e.getComponent<TransformComponent>();
			auto &spring = e.getComponent<FixedSpringComponent>();

			if (spring.entity.hasComponent<TransformComponent>() && 
				spring.entity.hasComponent<ParticleComponent>())
			{
				auto &particle = spring.entity.getComponent<ParticleComponent>();
				auto &entityTransform = spring.entity.getComponent<TransformComponent>();

				Vector3 relativePosition = entityTransform.position - transform.position;
				float length = glm::length(relativePosition);
				float x = length - spring.restLength;
				Vector3 direction = glm::normalize(relativePosition);

				particle.AddForce(-spring.springConstant * x * direction);

				/*
				float g = 1.0f / (1.0f +  pow(abs(x), 0.5f));
				float r = 1 - g;

				Color color = Color(r, g, 0, 1);

				float deltaLength = length / 10.0f;
				for (int i = 0; i < 10; i++)
				{
					getWorld().data.renderUtil->DrawCube(
						transform.position + (float)i * deltaLength * direction,
						Vector3(0.1f, 0.1f, 0.1f) * min((spring.springConstant / 10.0f), 5.0f), Vector3(0,0,0), color);
				}

				getWorld().data.renderUtil->DrawLine(
					transform.position, transform.position + length * direction, color);*/
			}
		}

	}
}
