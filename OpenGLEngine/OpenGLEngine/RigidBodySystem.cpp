#include "RigidbodySystem.h"
#include "BodyData.h"

namespace Reality
{
	RigidbodySystem::RigidbodySystem(rp3d::CollisionWorld& _rp3dWorld)
		:rp3dWorld(_rp3dWorld)
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

			// Initialize rigidbody for rp3d
			if (!rigidbody.initialized)
			{
				reactphysics3d::Vector3 position = reactphysics3d::Vector3(
					transform.GetPosition().x,
					transform.GetPosition().y,
					transform.GetPosition().z);
				reactphysics3d::Quaternion quat = reactphysics3d::Quaternion(
					transform.GetOrientation().x,
					transform.GetOrientation().y,
					transform.GetOrientation().z,
					transform.GetOrientation().w
				);
				reactphysics3d::Transform rp3dTransform = reactphysics3d::Transform(position, quat);
				rigidbody.rp3dCollisionBody = rp3dWorld.createCollisionBody(rp3dTransform);
				rigidbody.rp3dCollisionBody->setUserData(new BodyData(e));
				rigidbody.initialized = true;
			}

			rigidbody.velocity += rigidbody.acceleration * deltaTime;
			transform.SetPosition(transform.GetPosition() + rigidbody.velocity * deltaTime);

			rigidbody.angularVelocity += rigidbody.angularAcceleration * deltaTime;
			Quaternion deltaRot = Quaternion(0, rigidbody.angularVelocity * deltaTime);
			transform.SetOrientation(glm::normalize(transform.GetOrientation() + 0.5f * deltaRot * transform.GetOrientation()));
		}
	}
}
