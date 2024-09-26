#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ForceAccumulatorComponent
	{
		ForceAccumulatorComponent(float mass = 1.0f) :
			inverseMass(1 / mass), forceAccumulator(Vector3(0, 0, 0))
		{

		}

		float inverseMass;

		inline void AddForce(Vector3 force)
		{
			forceAccumulator += force;
		}

		inline Vector3 GetAccumulatedForce()
		{
			return forceAccumulator;
		}

		inline void ResetForceAccumulator()
		{
			forceAccumulator = Vector3(0, 0, 0);
		}

	private:
		Vector3 forceAccumulator;
	};
}
