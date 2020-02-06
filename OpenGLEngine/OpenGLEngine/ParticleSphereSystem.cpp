#include "ParticleSphereSystem.h"
#include "TransformComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	ParticleSphereSystem::ParticleSphereSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<ParticleSphereComponent>();
	}

	void ParticleSphereSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			if (DEBUG_LOG_LEVEL > 0)
			{

				getWorld().data.renderUtil->DrawSphere(
					e.getComponent<TransformComponent>().position,
					e.getComponent<ParticleSphereComponent>().radius,
					Color::Orange
				);
			}
		}

		if (getEntities().size() > 1)
		{
			for (int i = 0; i < getEntities().size() - 1; ++i)
			{
				for (int j = i + 1; j < getEntities().size(); j++)
				{
					if (CheckCollision(getEntities()[i], getEntities()[j]) && DEBUG_LOG_LEVEL > 0)
					{
						getWorld().data.renderUtil->DrawLine(
							getEntities()[i].getComponent<TransformComponent>().position,
							getEntities()[j].getComponent<TransformComponent>().position,
							Color::Red
						);
					}
				}
			}
		}
	}

	bool ParticleSphereSystem::CheckCollision(ECSEntity sphereA, ECSEntity sphereB)
	{
		Vector3 posA = sphereA.getComponent<TransformComponent>().position;
		Vector3 posB = sphereB.getComponent<TransformComponent>().position;
		float r1 = sphereA.getComponent<ParticleSphereComponent>().radius;
		float r2 = sphereB.getComponent<ParticleSphereComponent>().radius;

		if (glm::distance(posA, posB) < r1 + r2)
		{
			getWorld().getEventManager().emitEvent<ParticleContactEvent>(
				sphereA,
				sphereB,
				1.f,
				glm::normalize(posA - posB),
				r1 + r2 - glm::distance(posA, posB));

			return true;
		}

		return false;
	}

}
