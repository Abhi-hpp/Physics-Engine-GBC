#include "SphereColliderSystem.h"

namespace Reality
{
	SphereColliderSystem::SphereColliderSystem(rp3d::CollisionWorld& _rp3dWorld)
		:rp3dWorld(_rp3dWorld)
	{
		requireComponent<SphereColliderComponent>();
		requireComponent<RigidbodyComponent>();
	}

	void SphereColliderSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& sphereCollider = e.getComponent<SphereColliderComponent>();
			auto& rigidbody = e.getComponent<RigidbodyComponent>();

			if (!sphereCollider.initialized && rigidbody.initialized)
			{
				reactphysics3d::Transform rp3dTransform = reactphysics3d::Transform();
				rp3d::SphereShape sphere(sphereCollider.radius);
				sphereCollider.proxyShape = rigidbody.rp3dCollisionBody->addCollisionShape(&sphere, rp3dTransform);
				sphereCollider.proxyShape->setUserData(&sphereCollider);
				sphereCollider.initialized = true;
			}
		}
	}
}
