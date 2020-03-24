#include "LifeTimeSystem.h"

namespace Reality
{
	LifeTimeSystem::LifeTimeSystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<LifeTimeComponent>();
	}

	void LifeTimeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& lifeTime = e.getComponent<LifeTimeComponent>();

			getWorld().data.renderUtil->DrawSphere(transform.GetPosition(), 1.0f, lifeTime.color);

			lifeTime.timer += deltaTime;
			if (lifeTime.timer >= lifeTime.maxTime)
			{
				e.kill();
			}
		}
	}
}
