#include "BuoyancyResolutionSystem.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"
#include "BuoyancyComponent.h"
#include "DragForceComponent.h"

namespace Reality
{
	BuoyancyResolutionSystem::BuoyancyResolutionSystem()
	{

	}

	void BuoyancyResolutionSystem::Update(float deltaTime)
	{
		spawnPoint = getWorld().data.renderUtil->camera.Position + (2.0f * getWorld().data.renderUtil->camera.Front);

		auto buoyancyEvent = getWorld().getEventManager().getEvents<BuoyancyControlEvent>();
		for (auto b : buoyancyEvent)
		{
			if (b.command == "Space")
				spawnVolume(spawnPoint);
			else if (b.command == "Plus")
				incrementDensity();
			else if (b.command == "Minus")
				decrementDensity();
		}
	}

	void BuoyancyResolutionSystem::spawnVolume(Vector3 point)
	{
		auto particle = getWorld().createEntity();
		particle.addComponent<TransformComponent>(point);
		particle.addComponent<ParticleComponent>(Vector3(0, 0, 0));
		particle.addComponent<ForceAccumulatorComponent>();
		particle.addComponent<GravityForceComponent>();
		particle.addComponent<BuoyancyComponent>(Vector3(10, 10, 10), 5, 1);
		particle.addComponent<DragForceComponent>(0.2f, 0.1f);
	}

	void BuoyancyResolutionSystem::incrementDensity()
	{
		int density = getWorld().getSystemManager().getSystem<BuoyancySystem>().liquidDensity += 10;
		
		density = min(max(0, density), min(density, 100));

		getWorld().getSystemManager().getSystem<BuoyancySystem>().liquidDensity = density;
	}

	void BuoyancyResolutionSystem::decrementDensity()
	{
		int density = getWorld().getSystemManager().getSystem<BuoyancySystem>().liquidDensity -= 10;

		density = max(max(0, density), min(density, 100));

		getWorld().getSystemManager().getSystem<BuoyancySystem>().liquidDensity = density;
	}
}
