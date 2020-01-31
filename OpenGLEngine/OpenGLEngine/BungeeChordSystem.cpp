#include "BungeeChordSystem.h"
#include "BungeeComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "TransformComponent.h"
#include "GravityForceComponent.h"

namespace Reality
{
	BungeeChordSystem::BungeeChordSystem()
	{
		requireComponent<BungeeChordComponent>();
	}

	void BungeeChordSystem::Update(float deltaTime)
	{
		GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;
		Camera& camera = getWorld().data.renderUtil->camera;

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spawnEnity && lastSpawnedEnity != ECSEntity())
		{
			Vector3 spawnLocation = camera.Position + camera.Front * 10.0f;

			auto newParticle = getWorld().createEntity();
			newParticle.addComponent<TransformComponent>(spawnLocation);
			newParticle.addComponent<ParticleComponent>(Vector3(0, 0, 0));
			newParticle.addComponent<ForceAccumulatorComponent>();
			newParticle.addComponent<GravityForceComponent>();

			auto newBungee = getWorld().createEntity();
			newBungee.addComponent<BungeeComponent>(20, 20, newParticle, lastSpawnedEnity);

			lastSpawnedEnity = newParticle;
			spawnEnity = true;
		}

		/*for (auto e : getEntities())
		{
			auto& bungeeSystem = e.getComponent<BungeeChordComponent>();

			if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS && !spawnEnity)
			{
				Vector3 spawnLocation = camera.Position + camera.Front * 10.0f;

				auto newParticle = getWorld().createEntity();
				newParticle.addComponent<TransformComponent>(spawnLocation);
				newParticle.addComponent<ParticleComponent>(Vector3(0, 0, 0));
				newParticle.addComponent<ForceAccumulatorComponent>();
				newParticle.addComponent<GravityForceComponent>();

				auto newBungee = getWorld().createEntity();
				newBungee.addComponent<BungeeComponent>(20, 20, newParticle, bungeeSystem.lastSpawnedEnity);

				bungeeSystem.lastSpawnedEnity = newParticle;	
				spawnEnity = true;
			}
		} */
	}
}
