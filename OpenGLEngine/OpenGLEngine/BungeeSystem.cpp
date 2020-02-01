#include "BungeeSystem.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
#include "GravityForceComponent.h"

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

			if (bungee.connectedEntityA.hasComponent<TransformComponent>()
				&& bungee.connectedEntityB.hasComponent<TransformComponent>())
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

					if (bungee.connectedEntityA.hasComponent<ForceAccumulatorComponent>() &&
						length >= bungee.restLength)
					{
						bungee.connectedEntityA.getComponent<ForceAccumulatorComponent>().AddForce(force);
					}

					if (bungee.connectedEntityB.hasComponent<ForceAccumulatorComponent>() &&
						length >= bungee.restLength)
					{
						bungee.connectedEntityB.getComponent<ForceAccumulatorComponent>().AddForce(-force);
					}

					if (DEBUG_LOG_LEVEL > 0)
					{
						getWorld().data.renderUtil->DrawLine(transformA.position, transformB.position,
							deltaL > 0 ? Color::Red : Color::Green);
					}
				}
			}
			GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;
			Camera& camera = getWorld().data.renderUtil->camera;

			static int oldState = GLFW_RELEASE;
			int newState = glfwGetKey(window, GLFW_KEY_SPACE);

			if (newState == GLFW_RELEASE && oldState == GLFW_PRESS)
			{
				//bungee.addComponent<BungeeComponent>(10, 20, entityA, entityB);

				auto& world = getWorld();
				auto entity = world.createEntity();
				entity.addComponent<TransformComponent>(Vector3(camera.Position.x, camera.Position.y, -50));
				entity.addComponent<ParticleComponent>(Vector3(10, 0, 0));
				entity.addComponent<ForceAccumulatorComponent>();
				entity.addComponent<GravityForceComponent>();

				auto tether = world.createEntity();
				tether.addComponent<BungeeComponent>(1, 50, bungee.lastEntity, entity, entity);

				// Update last object of chain
				bungee.lastEntity = tether.getComponent<BungeeComponent>().lastEntity;
			}
			oldState = newState;
		}
	}
}
