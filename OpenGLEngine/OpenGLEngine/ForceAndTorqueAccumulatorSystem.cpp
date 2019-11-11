#include "ForceAndTorqueAccumulatorSystem.h"

namespace Reality
{
	ForceAndTorqueAccumulatorSystem::ForceAndTorqueAccumulatorSystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RigidBodyComponent>();
	}

	void ForceAndTorqueAccumulatorSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &rigidbody = e.getComponent<RigidBodyComponent>();
			auto &transform = e.getComponent<TransformComponentV2>();

			rigidbody.accelaration = rigidbody.GetForce() * rigidbody.inverseMass;
			rigidbody.ResetForceAccumulator();

			Mat3 rotMat = transform.GetRotationMatrix();
			rigidbody.angularAccelaration = rigidbody.worldInverseInertiaTensor(rotMat)
				* rigidbody.GetTorque();
			rigidbody.ResetTorqueAccumulator();
		}
	}
}
