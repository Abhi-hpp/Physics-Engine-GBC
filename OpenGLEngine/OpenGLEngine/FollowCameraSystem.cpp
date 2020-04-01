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

			if (transform.GetPosition().y < -5)
			{
				transform.SetPosition(Vector3(transform.GetPosition().x, -5, transform.GetPosition().z));
			}
			if (transform.GetPosition().y > -2)
			{
				transform.SetPosition(Vector3(transform.GetPosition().x, -2, transform.GetPosition().z));
			}
			

			getWorld().data.renderUtil->camera.Position = transform.GetPosition() + /*transform.LocalToWorldDirection(follow.follow)*/ - cam.Front * 100.0f;
		}
	}
}
