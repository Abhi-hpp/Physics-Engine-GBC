#include "ForceAccumulatorSystem.h"


namespace Reality
{
	ForceAccumulatorSystem::ForceAccumulatorSystem()
	{
		requireComponent<ParticleComponent>();
	}


	void ForceAccumulatorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &particle = e.getComponent<ParticleComponent>();
			particle.accelaration = particle.GetForce() * particle.inverseMass;
			particle.ResetForceAccumulator();
		}
	}
}
