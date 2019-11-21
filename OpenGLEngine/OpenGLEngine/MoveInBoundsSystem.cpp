#include "MoveInBoundsSystem.h"
#include "RigidBodyComponent.h"
#include "SphereColliderComponent.h"
#include "BoxColliderComponent.h"
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
			bool spawn = false;
			if (abs(transform.GetPosition().x) > move.bounds.x && transform.GetPosition().x * move.velocity.x > 0)
			{
				spawn = true;
				//move.velocity.x *= -1;
			}
			if (abs(transform.GetPosition().y) > move.bounds.y && transform.GetPosition().y * move.velocity.y > 0)
			{
				spawn = true;
				//move.velocity.y *= -1;
			}
			if (abs(transform.GetPosition().z) > move.bounds.z && transform.GetPosition().z * move.velocity.z > 0)
			{
				spawn = true;
				//move.velocity.z *= -1;
			}
			transform.SetPosition(transform.GetPosition() + move.velocity * deltaTime);
			if (spawn)
			{
				/*auto en = getWorld().createEntity();
				en.addComponent<TransformComponentV2>(-transform.GetPosition());
				en.addComponent<RigidBodyComponent>();
				en.addComponent<MoveInBoundsComponent>(move.velocity, move.bounds);
				auto col = getWorld().createEntity();
				col.addComponent<SphereColliderComponent>(en, 30);*/
				auto en = getWorld().createEntity();
				en.addComponent<TransformComponentV2>(Vector3(RANDOM_FLOAT(-200.0f, 200.0f), RANDOM_FLOAT(-200.0f, 200.0f), RANDOM_FLOAT(-200.0f, 200.0f)),
					Vector3(1, 1, 1),
					Vector3(RANDOM_FLOAT(-180.0f, 180.0f), RANDOM_FLOAT(-180.0f, 180.0f), RANDOM_FLOAT(-180.0f, 180.0f)));
				en.addComponent<RigidBodyComponent>();
				en.addComponent<MoveInBoundsComponent>(Vector3(RANDOM_FLOAT(-10.0f, 10.0f), RANDOM_FLOAT(-10.0f, 10.0f), RANDOM_FLOAT(-10.0f, 10.0f)),
					Vector3(200, 200, 200));
				auto col = getWorld().createEntity();
				if ((RANDOM_FLOAT(0.0f, 1.0f) >= 0.5f))
				{
					col.addComponent<SphereColliderComponent>(en, RANDOM_FLOAT(10.0f, 50.0f));
				}
				else
				{
					col.addComponent<BoxColliderComponent>(en, Vector3(RANDOM_FLOAT(30.0f, 70.0f), RANDOM_FLOAT(30.0f, 70.0f), RANDOM_FLOAT(30.0f, 70.0f)));
				}
				e.kill();
			}
		}
	}
}
