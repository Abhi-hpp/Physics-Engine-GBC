#include "InfiniteSpawnSystem.h"
#include "SpawnTargetEvent.h"

namespace Reality
{
	InfiniteSpawnSystem::InfiniteSpawnSystem()
	{
		requireComponent<InfiniteSpawnComponent>();
		requireComponent<TransformComponentV2>();
	}

	void InfiniteSpawnSystem::Update(float deltaTime)
	{
		auto targetEvents = getWorld().getEventManager().getEvents<SpawnTargetEvent>();

		if (targetEvents.size() > 0)
		{
			Vector3 target = targetEvents[0].targetPos;

			for (auto e : getEntities())
			{
				auto& spawn = e.getComponent<InfiniteSpawnComponent>();
				auto& transform = e.getComponent<TransformComponentV2>();

				if (abs(target.z - transform.GetPosition().z) > 2050.0f)
				{
					transform.SetPosition(transform.GetPosition() + (target.z > transform.GetPosition().z ? 4050.0f : -4050.0f) * Vector3(0, 0, 1));
					spawn.height = RANDOM_FLOAT(100.0f, 500.0f);
				}
				getWorld().data.renderUtil->DrawCube(transform.GetPosition() + spawn.height * 0.5f * Vector3(0, 1, 0), Vector3(50.0f, spawn.height, 50.0f));
			}
		}	
	}
}
