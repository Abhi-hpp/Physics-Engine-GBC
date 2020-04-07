#include "LifeTimeSystem.h"

namespace Reality
{
	LifeTimeSystem::LifeTimeSystem()
	{
<<<<<<< Updated upstream
		requireComponent<LifeTimeComponent>();
		requireComponent<TransformComponentV2>();
=======
		requireComponent<TransformComponentV2>();
		requireComponent<LifeTimeComponent>();
>>>>>>> Stashed changes
	}

	void LifeTimeSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
<<<<<<< Updated upstream
			auto& life = e.getComponent<LifeTimeComponent>();
			auto& transform = e.getComponent<TransformComponentV2>();

			life.timer += deltaTime;
			life.size = life.startSize + 10.0f * pow(life.timer, 0.5f);
			getWorld().data.renderUtil->DrawSphere(transform.GetPosition(), life.size, Color::Yellow);
			if (life.timer > life.maxTime)
=======
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& lifeTime = e.getComponent<LifeTimeComponent>();

			getWorld().data.renderUtil->DrawSphere(transform.GetPosition(), 1.0f, lifeTime.color);

			lifeTime.timer += deltaTime;
			if (lifeTime.timer >= lifeTime.maxTime)
>>>>>>> Stashed changes
			{
				e.kill();
			}
		}
	}
}
