#include "RigidBodySystem.h"

namespace Reality
{
	RigidBodySystem::RigidBodySystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RigidBodyComponent>();
	}

	void RigidBodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &rigidbody = e.getComponent<RigidBodyComponent>();
			auto &transform = e.getComponent<TransformComponentV2>();

			// Update velocity from accelarartion
			rigidbody.velocity += rigidbody.accelaration * deltaTime;
			rigidbody.angularVelocity += rigidbody.angularAccelaration * deltaTime;

			// Damping
			rigidbody.velocity *= pow(1.0f - rigidbody.linearDamping, deltaTime);
			rigidbody.angularVelocity *= pow(1.0f - rigidbody.angularDamping, deltaTime);
			
			transform.SetPosition(transform.GetPosition() + rigidbody.velocity * deltaTime);
			glm::quat angularVelocityQuat = glm::quat(0, rigidbody.angularVelocity.x, rigidbody.angularVelocity.y, rigidbody.angularVelocity.z);
			transform.SetOrientation(glm::normalize(transform.GetOrientation() + 0.5f * angularVelocityQuat * transform.GetOrientation() * deltaTime));
		}
	}
}
