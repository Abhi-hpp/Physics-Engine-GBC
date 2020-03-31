#include "GravityForceSystem.h"

namespace Reality
{
	GravityForceSystem::GravityForceSystem()
	{
		requireComponent<ForceAndTorqueAccumulatorComponent>();
		requireComponent<GravityForceComponent>();
	}

	void GravityForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& forceAcc = e.getComponent<ForceAndTorqueAccumulatorComponent>();
			auto& gravity = e.getComponent<GravityForceComponent>();

			if (forceAcc.inverseMass > 0)
			{
				forceAcc.AddForce(worldGravity * gravity.gravityScale / forceAcc.inverseMass);
			}
		}
	}
}
