#include "BuoyancySystem.h"
#include <time.h>
namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<TransformComponentV2>();
		requireComponent<RigidBodyComponent>();
		requireComponent<BuoyancyComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto &rigidBody = e.getComponent<RigidBodyComponent>();
			auto &transform = e.getComponent<TransformComponentV2>();
			auto &buoyancyComp = e.getComponent<BuoyancyComponent>();

			srand(time(NULL));

			float depth = buoyancyComp.GetWaterHeight() - transform.GetPosition().y;


			// if boat under waterheight apply force at random rate
			if (transform.GetPosition().y <= buoyancyComp.GetWaterHeight())
			{
				
					
					rigidBody.AddForce(
						Vector3(0, (depth 
							* (rigidBody.gravityScale / rigidBody.inverseMass)) 
							* buoyancyComp.GetLiquidDensity(), 0)
					);


			}
			
			


		}
	}
}