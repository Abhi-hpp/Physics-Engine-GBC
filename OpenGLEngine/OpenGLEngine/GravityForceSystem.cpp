#include "GravityForceSystem.h"

namespace Reality
{
	GravityForceSystem::GravityForceSystem()
	{
		requireComponent<ForceAccumulatorComponent>();
		requireComponent<GravityForceComponent>();
	}

	void GravityForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& gravity = e.getComponent<GravityForceComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();

			if (forceAcc.inverseMass > 0)
			{
				forceAcc.AddForce(worldGravity * gravity.gravityScale / forceAcc.inverseMass);
			}
		}
	}
}
