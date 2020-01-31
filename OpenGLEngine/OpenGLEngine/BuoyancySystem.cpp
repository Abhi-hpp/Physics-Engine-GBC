#include "BuoyancySystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponent>();
	}

	void BuoyancySystem::Update(float deltaTime)
	{
	
		for (auto e : getEntities())
		{
			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& transform = e.getComponent<TransformComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();

			float deltaDensity = (buoyancy.liquidDensity -800) / 700;

			float g = deltaDensity;
			float r = 1 - g;

			Color col = Color(r, g, 0, 1);

			// draw  body of water based on water dimensions
			getWorld().data.renderUtil->DrawCube(Vector3(0.0f, -waterDimensions.y/2 + buoyancy.waterHeight , 0.0f), waterDimensions, Vector3(0, 0, 0), col);

			// draw the floaty object
			getWorld().data.renderUtil->DrawCube(transform.position, buoyancy.dimensions, Vector3(0, 0, 0), Color::Green);
			
			
				if (transform.position.x - buoyancy.dimensions.x/2 < waterDimensions.x / 2 // if left edge is within the bounds
					&& transform.position.x + buoyancy.dimensions.x> -waterDimensions.x / 2 // if right edge is within the bounds
					&& transform.position.z + buoyancy.dimensions.z/2 < waterDimensions.z / 2 // if back is within the bounds
					&& transform.position.z - buoyancy.dimensions.z / 2 > -waterDimensions.z / 2) // if the front is within the bounds
				{
					float depth = transform.position.y - buoyancy.dimensions.y/2;// location of the bottom of the floaty object
					Vector3 force(0, 0, 0);
					float totalVolume = buoyancy.dimensions.x * buoyancy.dimensions.y * buoyancy.dimensions.z;

					//out of water
					if (depth >= buoyancy.waterHeight)
					{
						//can adjust the drag component here to be for air
						
					}

					// maximum depth
					else if (depth <= buoyancy.waterHeight - buoyancy.dimensions.y && depth + buoyancy.dimensions.y > -waterDimensions.y + buoyancy.waterHeight) // check if the floaty object is fully submerged in the water and not below
					{
						force.y = deltaTime * buoyancy.liquidDensity * totalVolume;
					
						forceAcc.AddForce(force);
						
						
					}
					else if(depth + buoyancy.dimensions.y > -waterDimensions.y + buoyancy.waterHeight) // make sure it isnt below (check the top of the buoyancy object vs the bottom of the water)
					{
						//partially submerged
						force.y = deltaTime * buoyancy.liquidDensity * totalVolume * (buoyancy.waterHeight - depth) * buoyancy.dimensions.x * buoyancy.dimensions.z;
						forceAcc.AddForce(force);
					}
				}

				
		}

	}
}
