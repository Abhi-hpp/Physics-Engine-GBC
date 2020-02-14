#include "RotateSystem.h"

namespace Reality
{
	RotateSystem::RotateSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<RotateComponent>();
	}

	void RotateSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponent>();
			auto& rotate = e.getComponent<RotateComponent>();

			transform.eulerAngles += rotate.rotationVelocity * deltaTime;
		}
	}
}
