#include "RotateSystem.h"
#include "LifeTimeComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	RotateSystem::RotateSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<RotateComponent>();
	}

	void RotateSystem::Update(float deltaTime)
	{
		timer += deltaTime;
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponent>();
			auto& rotate = e.getComponent<RotateComponent>();

			transform.eulerAngles += rotate.rotationVelocity * deltaTime;

			if (timer >= 0.1f)
			{
				auto e1 = getWorld().createEntity();
				e1.addComponent<TransformComponentV2>(transform.position + transform.Up() * 10.0f);
				e1.addComponent<LifeTimeComponent>();

				auto e2 = getWorld().createEntity();
				e2.addComponent<TransformComponentV2>(transform.position + transform.Right() * 10.0f);
				e2.addComponent<LifeTimeComponent>(5, Color::Red);

				auto e3 = getWorld().createEntity();
				e3.addComponent<TransformComponentV2>(transform.position + transform.Forward() * 10.0f);
				e3.addComponent<LifeTimeComponent>(5, Color::Blue);
			}
		}
		if (timer >= 0.1f)
		{
			timer = 0;
		}

		//getWorld().data.renderUtil->RenderText("Euler Angles", 350, 200, 1, Color::Orange);
	}
}
