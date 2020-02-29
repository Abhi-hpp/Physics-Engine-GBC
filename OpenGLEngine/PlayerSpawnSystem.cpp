#include "PlayerSpawnSystem.h"
#include "TriangleSystem.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"
#include "PenetrationDeltaMoveComponent.h"

namespace Reality
{
	PlayerSpawnSystem::PlayerSpawnSystem()
	{
	}

	void PlayerSpawnSystem::Update(float deltaTime)
	{
		GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;

		if (glfwGetKey(window, GLFW_KEY_E) == GLFW_PRESS)
		{
			Vector3 spawnLocation = Vector3(RANDOM_FLOAT(lowerX, upperX), height, RANDOM_FLOAT(lowerZ, upperZ));
			player.kill();
			createPlayer(spawnLocation);
		}
	}

	void PlayerSpawnSystem::createPlayer(Vector3 spawnLocation)
	{
		auto e = getWorld().createEntity();
		e.addComponent<TransformComponent>(spawnLocation);
		e.addComponent<ParticleComponent>();
		e.addComponent<ForceAccumulatorComponent>();
		e.addComponent<GravityForceComponent>();
		e.addComponent<PenetrationDeltaMoveComponent>();
		getWorld().getSystemManager().getSystem<TriangleSystem>().setPlayerEntity(e);

		setPlayerEntity(e);
	}
}
