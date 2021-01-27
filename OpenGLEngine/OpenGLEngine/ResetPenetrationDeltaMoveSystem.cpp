#include "ResetPenetrationDeltaMoveSystem.h"

namespace Reality
{
	ResetPenetrationDeltaMoveSystem::ResetPenetrationDeltaMoveSystem()
	{
		requireComponent<PenetrationDeltaMoveComponent>();
	}

	void ResetPenetrationDeltaMoveSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& penetration = e.getComponent<PenetrationDeltaMoveComponent>();
			penetration.deltaMove = Vector3(0, 0, 0);
		}
	}
}
