#include "GravitySystem.h"

namespace Reality
{
	GravitySystem::GravitySystem()
	{
		requireComponent<ForceAndTorqueAccumulatorComponent>();
		requireComponent<GravityComponent>();
	}

	void GravitySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& forceAcc = e.getComponent<ForceAndTorqueAccumulatorComponent>();
			auto& gravity = e.getComponent<GravityComponent>();

			if (forceAcc.inverseMass > 0)
			{
				forceAcc.AddForce(worldGravity * gravity.gravityScale / forceAcc.inverseMass);
			}
		}
	}
}
