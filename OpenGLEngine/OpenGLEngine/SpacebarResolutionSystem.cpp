#include "SpacebarResolutionSystem.h"
#include "TransformComponent.h"
#include "ParticleComponent.h"
#include "ForceAccumulatorComponent.h"
#include "GravityForceComponent.h"
#include "BungeeChordComponent.h"
#include "BungeeEndComponent.h"

namespace Reality
{
	SpacebarResolutionSystem::SpacebarResolutionSystem()
	{

	}

	void SpacebarResolutionSystem::Update(float deltaTime)
	{
		auto bungeeEvents = getWorld().getEventManager().getEvents<SpawnBungeeEvent>();
		for (auto bungeEvent : bungeeEvents)
		{
			ExtendBungeeChain(bungeEvent);
		}
	}

	void SpacebarResolutionSystem::ExtendBungeeChain(SpawnBungeeEvent& bungeEvent)
	{
		spawnPoint = getWorld().data.renderUtil->camera.Position + (5.0f * getWorld().data.renderUtil->camera.Front);

		auto particle = getWorld().createEntity();
		particle.addComponent<TransformComponent>(spawnPoint);
		particle.addComponent<ParticleComponent>(Vector3(0, 0, 0));
		particle.addComponent<ForceAccumulatorComponent>();
		particle.addComponent<GravityForceComponent>();
		particle.addComponent<BungeeEndComponent>();

		auto bungee = getWorld().createEntity();
		bungee.addComponent<BungeeChordComponent>(10.0f, 10.0f, bungeEvent.entity, particle);
	}
}
