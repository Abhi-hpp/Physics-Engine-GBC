#include "RigidbodySystem.h"

namespace Reality
{
	RigidbodySystem::RigidbodySystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RigidbodyComponent>();
	}

	void RigidbodySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& rigidbody = e.getComponent<RigidbodyComponent>();

			rigidbody.velocity += rigidbody.acceleration * deltaTime;
			transform.SetPosition(transform.GetPosition() + rigidbody.velocity * deltaTime);

			rigidbody.angularVelocity += rigidbody.angularAcceleration * deltaTime;
			Quaternion deltaRot = Quaternion(0, rigidbody.angularVelocity * deltaTime);
			transform.SetOrientation(glm::normalize(transform.GetOrientation() + 0.5f * deltaRot * transform.GetOrientation()));
		}
	}
}
