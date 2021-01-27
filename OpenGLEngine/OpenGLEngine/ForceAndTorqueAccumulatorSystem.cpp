#include "ForceAndTorqueAccumulatorSystem.h"

namespace Reality
{
	ForceAndTorqueAccumulatorSystem::ForceAndTorqueAccumulatorSystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RigidbodyComponent>();
		requireComponent<ForceAndTorqueAccumulatorComponent>();
	}

	void ForceAndTorqueAccumulatorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& rigidbody = e.getComponent<RigidbodyComponent>();
			auto& forceAndTorqueAcc = e.getComponent<ForceAndTorqueAccumulatorComponent>();

			rigidbody.acceleration = forceAndTorqueAcc.GetAccumulatedForce() * forceAndTorqueAcc.inverseMass;
			forceAndTorqueAcc.ResetForceAccumulator();

			Mat3 worldInvInertia = forceAndTorqueAcc.GetWorldInverseInertiaTensor(transform.GetRotationMatrix());
			rigidbody.angularAcceleration = worldInvInertia * forceAndTorqueAcc.GetAccumulatedTorque();
			forceAndTorqueAcc.ResetTorqueAccumulator();
		}
	}
}
