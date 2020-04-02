#include "GravityForceSystemV2.h"

namespace Reality
{
	GravityForceSystemV2::GravityForceSystemV2()
	{
		requireComponent<GravityForceComponentV2>();
		requireComponent<ForceAndTorqueAccumulatorComponent>();
	}

	void GravityForceSystemV2::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& forceAndTorque = e.getComponent<ForceAndTorqueAccumulatorComponent>();
			auto& gravity = e.getComponent<GravityForceComponentV2>();

			if (forceAndTorque.inverseMass > 0)
			{
				forceAndTorque.AddForce(worldGravity * gravity.gravityScale / forceAndTorque.inverseMass);
			}
		}
	}
}
