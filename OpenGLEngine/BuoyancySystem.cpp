#include "BuoyancySystem.h"
#include <time.h>
namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RigidBodyComponent>();
		requireComponent<Buoyancy>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &rigidbody = e.getComponent<RigidBodyComponent>();
			auto &transform = e.getComponent<TransformComponentV2>();
			auto &BuoyancyComp = e.getComponent<Buoyancy>();

			srand(time(NULL));

			float depth = BuoyancyComp.GetWaterHeight() - transform.GetPosition().y;


			// if boat under waterheight apply force at random rate
			if (transform.GetPosition().y <= BuoyancyComp.GetWaterHeight())
			{
				
					
					rigidbody.AddForce(
						Vector3(0, (depth * (rigidbody.gravityScale / rigidbody.inverseMass)) * BuoyancyComp.GetLiquidDensity(), 0)
					);

					// rigidbody.AddForceAtPoint(
					// 	Vector3(0, (rand() % 200), 0),
					// 	Vector3((rand() % 200), (rand() % 200), (rand() % 200)),
					// 	Vector3(0, 0, 0)
					// );

			}
			
			


		}
	}
}