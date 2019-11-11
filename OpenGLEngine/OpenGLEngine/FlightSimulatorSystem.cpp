#include "FlightSimulatorSystem.h"
#include "LifeTimeComponent.h"

namespace Reality
{
	FlightSimulatorSystem::FlightSimulatorSystem()
	{
		requireComponent<FlighSimulatorComponent>();
		requireComponent<RigidBodyComponent>();
		requireComponent<TransformComponentV2>();
	}

	void FlightSimulatorSystem::Update(float deltaTime)
	{
		timer += deltaTime;
		for (auto e : getEntities())
		{
			auto& rigidbody = e.getComponent<RigidBodyComponent>();
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& flight = e.getComponent<FlighSimulatorComponent>();

			rigidbody.AddForce(transform.LocalToWorldDirection(flight.propulsion));
			//rigidbody.AddForce(Vector3(0, -10, 0));

			// smoke
			if (timer > 0.1f)
			{
				/*for (int i = 0; i < 3; i++)
				{
					auto e = getWorld().createEntity();
					e.addComponent<TransformComponentV2>(transform.GetPosition() + Vector3(RANDOM_FLOAT(-5.0f, 5.0f), RANDOM_FLOAT(-5.0f, 5.0f), RANDOM_FLOAT(-5.0f, 5.0f)) - transform.Forward() * 15.0f);
					e.addComponent<LifeTimeComponent>(7.0f);
				}*/
				auto e = getWorld().createEntity();
				e.addComponent<TransformComponentV2>(transform.GetPosition() - transform.Forward() * 15.0f);
				e.addComponent<LifeTimeComponent>(7.0f);
				timer = 0;
			}

			//if (timer > 5)
			//{
			//	auto& rigidbody = e.getComponent<RigidBodyComponent>();
			//	auto& transform = e.getComponent<TransformComponentV2>();
			//	auto& flight = e.getComponent<FlighSimulatorComponent>();

			//	//rigidbody.AddTorque(Vector3(RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1), RANDOM_FLOAT(-1, 1)) * 10.0f);
			//	rigidbody.AddForce(transform.Forward() * flight.propulsion);
			//	timer = 0;
			//}
		}
	}
}
