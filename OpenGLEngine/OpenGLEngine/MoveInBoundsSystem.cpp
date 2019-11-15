#include "MoveInBoundsSystem.h"

namespace Reality
{
	MoveInBoundsSystem::MoveInBoundsSystem()
	{
		requireComponent<MoveInBoundsComponent>();
		requireComponent<TransformComponentV2>();
	}

	void MoveInBoundsSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& move = e.getComponent<MoveInBoundsComponent>();
			auto& transform = e.getComponent<TransformComponentV2>();

			if (abs(transform.GetPosition().x) > move.bounds.x && transform.GetPosition().x * move.velocity.x > 0)
			{
				move.velocity.x *= -1;
			}
			if (abs(transform.GetPosition().y) > move.bounds.y && transform.GetPosition().y * move.velocity.y > 0)
			{
				move.velocity.y *= -1;
			}
			if (abs(transform.GetPosition().z) > move.bounds.z && transform.GetPosition().z * move.velocity.z > 0)
			{
				move.velocity.z *= -1;
			}
			transform.SetPosition(transform.GetPosition() + move.velocity * deltaTime);
		}
	}
}
