#include "GravityForceSystemV2.h"

namespace Reality
{
	GravityForceSystemV2::GravityForceSystemV2()
	{
		requireComponent<ForceAndTorqueAccumulatorComponent>();
		requireComponent<GravityForceComponentV2>();
	}

	void GravityForceSystemV2::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& forceAndTorqueAcc = e.getComponent<ForceAndTorqueAccumulatorComponent>();
			auto& gravity = e.getComponent<GravityForceComponentV2>();

			if (forceAndTorqueAcc.inverseMass > 0)
			{
				forceAndTorqueAcc.AddForce(worldGravity * gravity.gravityScale / forceAndTorqueAcc.inverseMass);
			}
		}
	}
}
