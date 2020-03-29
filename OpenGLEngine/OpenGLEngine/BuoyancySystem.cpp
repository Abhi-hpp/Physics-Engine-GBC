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
<<<<<<< Updated upstream
=======
			GLFWwindow *window = getWorld().data.renderUtil->window->glfwWindow;

>>>>>>> Stashed changes

			srand(time(NULL));

			float depth = BuoyancyComp.GetWaterHeight() - transform.GetPosition().y;


			// if boat under waterheight apply force at random rate
			if (transform.GetPosition().y <= BuoyancyComp.GetWaterHeight())
			{
<<<<<<< Updated upstream
				
					
					rigidbody.AddForce(
						Vector3(0, (depth * (rigidbody.gravityScale / rigidbody.inverseMass)) * BuoyancyComp.GetLiquidDensity(), 0)
					);

					// rigidbody.AddForceAtPoint(
					// 	Vector3(0, (rand() % 200), 0),
					// 	Vector3((rand() % 200), (rand() % 200), (rand() % 200)),
					// 	Vector3(0, 0, 0)
					// );
=======
				rigidbody.AddForce(
					Vector3(0, (depth * (rigidbody.gravityScale / rigidbody.inverseMass)) * BuoyancyComp.GetLiquidDensity(), 0)
				);
			}



			if ((glfwGetKey(window, GLFW_KEY_W) != GLFW_PRESS) &&
				(glfwGetKey(window, GLFW_KEY_S) != GLFW_PRESS))
			{
		
				
				// Pitch
				if ((rand() % 100 - 1) % 2 == 1)
				{
					rigidbody.AddForceAtPoint(
						Vector3(0, 0.4, 0),
						Vector3(0, 0, 0.00008),
						BuoyancyComp.GetCenterOfBuoyancy()
					);
				}

				if(((rand() % 100 - 1) % 2 == 1))
				{
					rigidbody.AddForceAtPoint(
						Vector3(0, 0.4, 0),
						Vector3(0, 0, -0.00008),
						BuoyancyComp.GetCenterOfBuoyancy()
					);
				}

				// Roll
				if ((rand() % 100 - 1) % 2 == 1)
				{
					rigidbody.AddForceAtPoint(
						Vector3(0, 0.4, 0),
						Vector3(0.00008, 0, 0),
						BuoyancyComp.GetCenterOfBuoyancy()
					);
				}
				
				if(((rand() % 100 - 1) % 2 == 1))
				{
					rigidbody.AddForceAtPoint(
						Vector3(0, 0.4, 0),
						Vector3(-0.00008, 0, 0),
						BuoyancyComp.GetCenterOfBuoyancy()
					);
				}
>>>>>>> Stashed changes

			}
			
			


		}
	}
}