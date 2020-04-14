#include "FollowCameraSystem.h"

namespace Reality
{
	FollowCameraSystem::FollowCameraSystem()
	{
		requireComponent<FollowCameraComponent>();
		requireComponent<TransformComponentV2>();
	}

	void FollowCameraSystem::Update(float deltaTime)
	{
		Camera& cam = getWorld().data.renderUtil->camera;
		for (auto e : getEntities())
		{
			auto& follow = e.getComponent<FollowCameraComponent>();
			auto& transform = e.getComponent<TransformComponentV2>();
			getWorld().data.renderUtil->camera.Position = transform.GetPosition() + /*transform.LocalToWorldDirection(follow.follow)*/ - cam.Front * 100.0f;
		}
	}
}
