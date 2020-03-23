#include "RotateSystemV2.h"
#include <glm/gtx/quaternion.hpp>
#include "LifeTimeComponent.h"

namespace Reality
{
	RotateSystemV2::RotateSystemV2()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RotateComponentV2>();
	}

	void RotateSystemV2::Update(float deltaTime)
	{
		timer += deltaTime;
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& rotate = e.getComponent<RotateComponentV2>();

			Vector3 axis = glm::normalize(rotate.rotationVelocity);
			float angle = glm::radians(glm::length(rotate.rotationVelocity)) * deltaTime;

			Quaternion deltaQuat = glm::angleAxis(angle, axis);
			Quaternion newRot = glm::normalize(deltaQuat * transform.GetOrientation());

			transform.SetOrientation(newRot);

			if (timer >= 0.1f)
			{
				auto e1 = getWorld().createEntity();
				e1.addComponent<TransformComponentV2>(transform.GetPosition() + transform.Up() * 10.0f);
				e1.addComponent<LifeTimeComponent>();

				auto e2 = getWorld().createEntity();
				e2.addComponent<TransformComponentV2>(transform.GetPosition() + transform.Right() * 10.0f);
				e2.addComponent<LifeTimeComponent>(5, Color::Red);

				auto e3 = getWorld().createEntity();
				e3.addComponent<TransformComponentV2>(transform.GetPosition() + transform.Forward() * 10.0f);
				e3.addComponent<LifeTimeComponent>(5, Color::Blue);
			}
		}
		if (timer >= 0.1f)
		{
			timer = 0;
		}

		//getWorld().data.renderUtil->RenderText("Quaternions", 1300, 200, 1, Color::Orange);
	}
}
