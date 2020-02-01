#include "PairedBungeeSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	PairedBungeeSystem::PairedBungeeSystem()
	{
		requireComponent<PairedBungeeComponent>();
	}

	void PairedBungeeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& bungee = e.getComponent<PairedBungeeComponent>();

			if (bungee.connectedEntityA.hasComponent<TransformComponent>() && bungee.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = bungee.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = bungee.connectedEntityB.getComponent<TransformComponent>();

				Vector3 relativePosition = transformA.position - transformB.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - bungee.restLength;
					Vector3 force = -glm::normalize(relativePosition);
					force *= bungee.springConstant * deltaL;

					if (length > bungee.restLength)
					{
						if (bungee.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
						{
							bungee.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
						}
						if (bungee.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
						{
							bungee.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
						}
					}



					float g = 1.0f / (1.0f + pow(abs(deltaL), 0.5f));
					float r = 1 - g;

					Color col = Color(r, g, 0, 1);

					float deltaLength = length / 10.0f;
					Vector3 direction = glm::normalize(relativePosition);
					for (int i = 0; i < 10; i++)
					{
						getWorld().data.renderUtil->DrawCube(
							transformB.position + (float)i * deltaLength * direction,
							Vector3(1.0f, 1.0f, 1.0f) * min((bungee.restLength / 20.0f), 100.0f), Vector3(0, 0, 0), col);
					}
					getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position, col);
				}

			}
		}
	}
}
