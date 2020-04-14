#include "LifeTimeSystem.h"

namespace Reality
{
	LifeTimeSystem::LifeTimeSystem()
	{
		requireComponent<LifeTimeComponent>();
		requireComponent<TransformComponentV2>();
	}

	void LifeTimeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& life = e.getComponent<LifeTimeComponent>();
			auto& transform = e.getComponent<TransformComponentV2>();

			life.timer += deltaTime;
			life.size = life.startSize + 10.0f * pow(life.timer, 0.5f);
			getWorld().data.renderUtil->DrawSphere(transform.GetPosition(), life.size, Color::Yellow);
			if (life.timer > life.maxTime)
			{
				e.kill();
			}
		}
	}
}
