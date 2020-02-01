#include "ForceAccumulatorSystem.h"

namespace Reality
{
	ForceAccumulatorSystem::ForceAccumulatorSystem()
	{
		requireComponent<ParticleComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	void ForceAccumulatorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& particle = e.getComponent<ParticleComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();

			if (forceAcc.inverseMass > 0)
			{
				particle.acceleration = forceAcc.GetAccumulatedForce() * forceAcc.inverseMass;
			}

			forceAcc.ResetForceAccumulator();
		}
	}
}
