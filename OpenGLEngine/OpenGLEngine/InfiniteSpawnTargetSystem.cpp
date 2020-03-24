#include "InfiniteSpawnTargetSystem.h"
#include "SpawnTargetEvent.h"

namespace Reality
{
	InfiniteSpawnTargetSystem::InfiniteSpawnTargetSystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<InfiniteSpawnTargetComponent>();
	}

	void InfiniteSpawnTargetSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			getWorld().getEventManager().emitEvent<SpawnTargetEvent>(transform.GetPosition());
		}
	}
}
