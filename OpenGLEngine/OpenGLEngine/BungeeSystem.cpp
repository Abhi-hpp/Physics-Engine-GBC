#include "BungeeSystem.h"
#include "TransformComponent.h"
#include "ForceAccumulatorComponent.h"
#include "ParticleComponent.h"
#include "GravityForceComponent.h"
#include "DragForceComponent.h"

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
			auto& bungeeTransform = e.getComponent<TransformComponent>();
			auto& bungee = e.getComponent<BungeeComponent>();

			GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;


			if (bungee.connectedEntity.hasComponent<ForceAccumulatorComponent>()
				&& bungee.connectedEntity.hasComponent<TransformComponent>())
			{
				auto& forceAcc = bungee.connectedEntity.getComponent<ForceAccumulatorComponent>();
				auto& transform = bungee.connectedEntity.getComponent<TransformComponent>();

				if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
				{
					auto particle1 = getWorld().createEntity();
					particle1.addComponent<TransformComponent>(transform.position);
					particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
					particle1.addComponent<ForceAccumulatorComponent>();
					particle1.addComponent<GravityForceComponent>();
					particle1.addComponent<DragForceComponent>(0, 0);


					//auto bungee1 = world.createEntity();
					bungee.connectedEntity.addComponent<TransformComponent>(transform.position);
					bungee.connectedEntity.addComponent<BungeeComponent>(5.0f, 300.0f, particle1);
					getWorld().data.renderUtil->DrawSphere(transform.position, 2.0f, Color::Cyan);
				}

				Vector3 relativePosition = transform.position - bungeeTransform.position;
				float length = glm::length(relativePosition);
				if (length > 0)
				{
					float deltaL = length - bungee.restLength;
					if (deltaL < 0)
					{
						Vector3 force = -glm::normalize(relativePosition);
						force *= bungee.springConstant * deltaL;
						forceAcc.AddForce(force);
						bungee.finalPosition = transform.position;
					}
					else
					{
						forceAcc.ResetAccumulator();
						transform.position = bungee.finalPosition;
					}

					Color col = Color(1, 0, 0, 1);

					getWorld().data.renderUtil->DrawLine(bungeeTransform.position, transform.position, col);
					getWorld().data.renderUtil->DrawSphere(transform.position);

				}
			}
		}
	}
}
