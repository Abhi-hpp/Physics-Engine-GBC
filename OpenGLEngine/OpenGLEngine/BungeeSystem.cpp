#include "BungeeSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BungeeSystem::BungeeSystem()
	{
		requireComponent<BungeeComponent>();
	}

	void BungeeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& bungee = e.getComponent<BungeeComponent>();


			//// Calculate the vector of the spring.
			//Vector3 force;
			//particle->getPosition(&force);
			//force -= other->getPosition();
			//// Check if the bungee is compressed.
			//real magnitude = force.magnitude();
			//if (magnitude <= restLength) return;
			//// Calculate the magnitude of the force.

			//magnitude = springConstant * (restLength - magnitude);
			//// Calculate the final force and apply it.
			//force.normalize();
			//force *= -magnitude;
			//particle->addForce(force);

			if (bungee.connectedEntityA.hasComponent<TransformComponent>() && bungee.connectedEntityB.hasComponent<TransformComponent>())
			{
				auto& transformA = bungee.connectedEntityA.getComponent<TransformComponent>();
				auto& transformB = bungee.connectedEntityB.getComponent<TransformComponent>();

				Vector3 relativePos = transformA.position - transformB.position;

				float length = glm::length(relativePos);
				if (length > bungee.restLength) {
					float deltaL = length - bungee.restLength;
					Vector3 force = -glm::normalize(relativePos);
					force *= bungee.springConstant * deltaL;


					if (bungee.connectedEntityA.hasComponent<ForceAccumulatorComponent>())
					{
						bungee.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					}


					if (bungee.connectedEntityB.hasComponent<ForceAccumulatorComponent>())
					{
						bungee.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
					}


				}
				getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position,
					Color::Purple);
			}

		}
	}
}
