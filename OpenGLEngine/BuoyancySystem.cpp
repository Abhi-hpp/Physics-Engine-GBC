#include "BuoyancySystem.h"
#include "ParticleComponent.h"
#include "GravityForceComponent.h"
#include "DragForceComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		GLFWwindow*  window = getWorld().data.renderUtil->window->glfwWindow;
		Camera& camera = getWorld().data.renderUtil->camera;

		if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS)
		{
			Vector3 spawnLocation = camera.Position + camera.Front * 30.0f;

			auto particle1 = getWorld().createEntity();
			particle1.addComponent<TransformComponent>(spawnLocation);
			particle1.addComponent<ForceAccumulatorComponent>();
			particle1.addComponent<ParticleComponent>(Vector3(0, 0, 0));
			particle1.addComponent<GravityForceComponent>(0.1f);
			particle1.addComponent<DragForceComponent>(0.05f, 0);
			particle1.addComponent<BuoyancyComponent>(4, 64);
		}

		if (glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS) { liquidDensity += 0.05f; }
		if (glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS) { liquidDensity -= 0.05f; }

		for (auto e : getEntities())
		{
			auto& force = e.getComponent<ForceAccumulatorComponent>();
			auto position = e.getComponent<TransformComponent>().position;
			auto buoy = e.getComponent<BuoyancyComponent>();

			float d = ((buoy.maxDepth / 2) - (position.y - liquidVolume.y)) / buoy.maxDepth;

			Color color = Color::Red;
			if (d <= 0) 
			{
				color = Color::Orange;
				//Force = 0 
			} 
			else if (d >= 1) 
			{ 
				color = Color::Blue;
				float vp = liquidDensity * buoy.volume;
				force.AddForce(Vector3(0, vp, 0));
			} 
			else // 0 < d < 1
			{ 
				color = Color::Green;
				float dvp = d * liquidDensity * buoy.volume;
				force.AddForce(Vector3(0, dvp, 0));
			}

			getWorld().data.renderUtil->DrawSphere(position, buoy.maxDepth, color);
			getWorld().data.renderUtil->DrawLine(liquidVolume, position, color);
		}
	}
}
