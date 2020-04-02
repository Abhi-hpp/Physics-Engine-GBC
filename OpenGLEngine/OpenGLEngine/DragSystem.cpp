#include "DragSystem.h"

namespace Reality
{
	DragSystem::DragSystem()
	{
		requireComponent<RigidbodyComponent>();
		requireComponent<DragComponent>();
	}

	void DragSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& rigidbody = e.getComponent<RigidbodyComponent>();
			auto& drag = e.getComponent<DragComponent>();

			rigidbody.velocity *= pow(1.0f - drag.linearDrag, deltaTime);
			rigidbody.angularVelocity *= pow(1.0f - drag.angularDrag, deltaTime);
		}
	}
}
