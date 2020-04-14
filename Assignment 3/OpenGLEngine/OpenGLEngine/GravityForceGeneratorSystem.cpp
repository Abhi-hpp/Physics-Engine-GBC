#include "GravityForceGeneratorSystem.h"


namespace Reality
{
	GravityForceGeneratorSystem::GravityForceGeneratorSystem()
	{
		requireComponent<ParticleComponent>();
	}


	void GravityForceGeneratorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &particle = e.getComponent<ParticleComponent>();
			particle.AddForce(gravity * particle.gravityScale / particle.inverseMass);
		}

	}
}
