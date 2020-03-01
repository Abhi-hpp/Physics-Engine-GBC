#include "PenetrationMovementResetSystem.h"

namespace Reality
{
	PenetrationMovementResetSystem::PenetrationMovementResetSystem()
	{
		requireComponent<PenetrationMovementComponent>();
	}

	void PenetrationMovementResetSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& penetration = e.getComponent<PenetrationMovementComponent>();
			penetration.deltaMove = Vector3(0, 0, 0);
		}
	}
}
