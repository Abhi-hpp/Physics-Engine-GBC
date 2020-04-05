#include "BungeeChordSystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BungeeChordSystem::BungeeChordSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BungeeChordComponent>();
	}

	void Reality::BungeeChordSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& bungee = e.getComponent<BungeeChordComponent>();

			Vector3 force;
			auto& BungeeTransform = e.getComponent<TransformComponent>();
			force -= bungee.otherTransform;

			float magnitude = sqrt((force.x * force.x) + (force.y * force.y) + (force.z * force.z));

			getWorld().data.renderUtil->DrawSphere(e.getComponent<TransformComponent>().position, 5.0f, Color::Red);
			if (magnitude <= bungee.restLength)
				return;

			force = Vector3(force.x / magnitude, force.y / magnitude, force.z / magnitude);
			magnitude = bungee.springConstant * (bungee.restLength - magnitude);

			force *= -magnitude;

			e.getComponent<TransformComponent>().position += force;
		}
	}
}