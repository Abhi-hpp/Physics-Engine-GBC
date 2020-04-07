#include "ForceAndTorqueAccumulatorSystem.h"

namespace Reality
{
	ForceAndTorqueAccumulatorSystem::ForceAndTorqueAccumulatorSystem()
	{
		requireComponent<TransformComponentV2>();
<<<<<<< Updated upstream
		requireComponent<RigidBodyComponent>();
=======
		requireComponent<RigidbodyComponent>();
		requireComponent<ForceAndTorqueAccumulatorComponent>();
>>>>>>> Stashed changes
	}

	void ForceAndTorqueAccumulatorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
<<<<<<< Updated upstream
			auto &rigidbody = e.getComponent<RigidBodyComponent>();
			auto &transform = e.getComponent<TransformComponentV2>();

			rigidbody.accelaration = rigidbody.GetForce() * rigidbody.inverseMass;
			rigidbody.ResetForceAccumulator();

			Mat3 rotMat = transform.GetRotationMatrix();
			rigidbody.angularAccelaration = rigidbody.worldInverseInertiaTensor(rotMat)
				* rigidbody.GetTorque();
			rigidbody.ResetTorqueAccumulator();
=======
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& rigidbody = e.getComponent<RigidbodyComponent>();
			auto& forceAndTorqueAcc = e.getComponent<ForceAndTorqueAccumulatorComponent>();

			rigidbody.acceleration = forceAndTorqueAcc.GetAccumulatedForce() * forceAndTorqueAcc.inverseMass;
			forceAndTorqueAcc.ResetForceAccumulator();

			Mat3 worldInvInertia = forceAndTorqueAcc.GetWorldInverseInertiaTensor(transform.GetRotationMatrix());
			rigidbody.angularAcceleration = worldInvInertia * forceAndTorqueAcc.GetAccumulatedTorque();
			forceAndTorqueAcc.ResetTorqueAccumulator();
>>>>>>> Stashed changes
		}
	}
}
