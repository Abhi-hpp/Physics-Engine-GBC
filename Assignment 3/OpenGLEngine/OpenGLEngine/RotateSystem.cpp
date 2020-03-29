#include "RotateSystem.h"

RotateSystem::RotateSystem()
{
	requireComponent<TransformComponent>();
	requireComponent<RotateComponent>();
}

void RotateSystem::Update(float deltaTime)
{
	for (auto e : getEntities())
	{
		auto &rotate = e.getComponent<RotateComponent>();
		auto &transform = e.getComponent<TransformComponent>();

		transform.eulerAngles.x += rotate.xRot * deltaTime;
		transform.eulerAngles.y += rotate.yRot * deltaTime;
		transform.eulerAngles.z += rotate.zRot * deltaTime;
	}
}
