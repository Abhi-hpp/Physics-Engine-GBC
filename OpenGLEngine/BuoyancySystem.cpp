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
			auto& liquidbuoyancy = e.getComponent<BuoyancyComponent>();
			auto& transform = e.getComponent<TransformComponent>();
			auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();

			float deltaDensity = (liquidbuoyancy.liquidDensity - 800) / 700;

			// changing color based on density.
			float g = deltaDensity;
			float r = 1 - g;

			// if blue the density is minimun, purple if density is max
			Color color = Color(r, g, 1, 1); 

			// draw floor
			getWorld().data.renderUtil->DrawCube(Vector3(0.0f, -liquidFloorDimensions.y/2 + liquidbuoyancy.liquidHeight , 0.0f), liquidFloorDimensions, Vector3(0, 0, 0), color);

			// draw cube objects to test
			getWorld().data.renderUtil->DrawCube(transform.position, liquidbuoyancy.dimensions, Vector3(0, 0, 0), Color::Red);
			
				// Set up floor bounds
				if (transform.position.x - liquidbuoyancy.dimensions.x/2 < liquidFloorDimensions.x / 2 // left edge bounds
					&& transform.position.x + liquidbuoyancy.dimensions.x> -liquidFloorDimensions.x / 2 // right edge bounds
					&& transform.position.z - liquidbuoyancy.dimensions.z / 2 > -liquidFloorDimensions.z / 2 // front bounds
					&& transform.position.z + liquidbuoyancy.dimensions.z/2 < liquidFloorDimensions.z / 2) // back bounds
					
				{
					float depth = transform.position.y - liquidbuoyancy.dimensions.y/2;//bottom location of the object
					Vector3 force(0, 0, 0);
					float totalVolume = liquidbuoyancy.dimensions.x * liquidbuoyancy.dimensions.y * liquidbuoyancy.dimensions.z;

					//out of the liquid
					if (depth >= liquidbuoyancy.liquidHeight)
					{
						
					}

					// maximum depth
					// runs a check to see if object is fully submerged in liquid 
					else if (depth <= liquidbuoyancy.liquidHeight - liquidbuoyancy.dimensions.y && depth + liquidbuoyancy.dimensions.y > -liquidFloorDimensions.y + liquidbuoyancy.liquidHeight)
					{
						force.y = deltaTime * liquidbuoyancy.liquidDensity * totalVolume;
					
						forceAcc.AddForce(force);
						
						
					}
					// check the top of the object vs the bottom of the liquid
					else if(depth + liquidbuoyancy.dimensions.y > -liquidFloorDimensions.y + liquidbuoyancy.liquidHeight) 
					{
						//partly submerged
						force.y = deltaTime * liquidbuoyancy.liquidDensity * totalVolume * (liquidbuoyancy.liquidHeight - depth) * liquidbuoyancy.dimensions.x * liquidbuoyancy.dimensions.z;
						forceAcc.AddForce(force);
					}
				}

				
		}

	}
}
