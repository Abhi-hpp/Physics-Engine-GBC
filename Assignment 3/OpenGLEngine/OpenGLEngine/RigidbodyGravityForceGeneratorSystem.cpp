#include "RigidbodyGravityForceGeneratorSystem.h"

namespace Reality
{
	RigidbodyGravityForceGeneratorSystem::RigidbodyGravityForceGeneratorSystem()
	{
		requireComponent<RigidBodyComponent>();
	}

	void RigidbodyGravityForceGeneratorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &body = e.getComponent<RigidBodyComponent>();
			if (body.inverseMass > 0)
			{
				body.AddForce(gravity * body.gravityScale / body.inverseMass);
			}
		}
	}
}
