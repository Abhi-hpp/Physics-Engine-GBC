#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ForceAccumulatorComponent
	{
		ForceAccumulatorComponent(float _mass = 1.0f, float mass = 1.0f)
			: inverseMass(1.0f / _mass), mass(_mass), forceAccumulator(Vector3(0, 0, 0))
		{

		}
		float inverseMass;
		float mass;

		inline void AddForce(Vector3 force)
		{
			forceAccumulator += force;
		}
		inline void ResetAccumulator()
		{
			forceAccumulator = Vector3(0, 0, 0);
		}
		inline Vector3 GetAccumulatedForce()
		{
			return forceAccumulator;
		}
	private:
		Vector3 forceAccumulator;
	};
}
