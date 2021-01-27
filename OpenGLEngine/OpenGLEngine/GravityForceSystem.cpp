#include "GravityForceSystem.h"
#include "ForceAndTorqueAccumulatorComponent.h"

namespace Reality
{
	GravityForceSystem::GravityForceSystem()
	{
		//requireComponent<ForceAccumulatorComponent>();
		requireComponent<GravityForceComponent>();
	}

	void GravityForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			if (e.hasComponent<ForceAccumulatorComponent>())
			{

				auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();
				auto& gravity = e.getComponent<GravityForceComponent>();

				if (forceAcc.inverseMass > 0)
				{
					forceAcc.AddForce(worldGravity * gravity.gravityScale / forceAcc.inverseMass);
				}
			}
			else if (e.hasComponent<ForceAndTorqueAccumulatorComponent>())
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
}
