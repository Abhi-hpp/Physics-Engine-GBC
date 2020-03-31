#include "BuoyancySystem.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "RigidbodyComponent.h"
#include "ThrusterComponent.h"
#include "LifeTimeComponent.h"

namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponentV2>();
		
	}

	void BuoyancySystem::Update(float deltaTime)
	{
	
		for (auto e : getEntities())
		{


			auto& buoyancy = e.getComponent<BuoyancyComponent>();
			auto& surfaceTransform = e.getComponent<TransformComponentV2>();

			if (buoyancy.targetEntity.hasComponent<TransformComponentV2>() &&
				buoyancy.targetEntity.hasComponent<RigidbodyComponent>() &&
				buoyancy.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{

				

				auto& targetTransform = buoyancy.targetEntity.getComponent<TransformComponentV2>();
				auto& rigidbody = buoyancy.targetEntity.getComponent<RigidbodyComponent>();
				auto& forceAcc = buoyancy.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				//draw the buoyancy component
				Vector3 worldSurfacePosition = targetTransform.LocalToWorldPosition(buoyancy.localOffset);
				surfaceTransform.SetPosition(worldSurfacePosition);
				surfaceTransform.SetOrientation(targetTransform.GetOrientation());
				getWorld().data.renderUtil->DrawCube(surfaceTransform.GetPosition(),
					buoyancy.dimensions,
					surfaceTransform.GetOrientation(), Color::Red);

				float deltaDensity = (buoyancy.liquidDensity - 800) / 700;

				float g = deltaDensity;
				float r = 1 - g;

				//Color col = Color(r, g, 0, 1);

				Color col = Color(0, 1, 0, 1);

				// draw  body of water based on water dimensions
				getWorld().data.renderUtil->DrawCube(Vector3(0.0f, -waterDimensions.y / 2 + buoyancy.waterHeight, 0.0f), waterDimensions, Vector3(0, 0, 0), col);

				if (surfaceTransform.GetPosition().x < waterDimensions.x / 2 // if left edge is within the bounds
					&& surfaceTransform.GetPosition().x > -waterDimensions.x / 2 // if right edge is within the bounds
					&& surfaceTransform.GetPosition().z < waterDimensions.z / 2 // if back is within the bounds
					&& surfaceTransform.GetPosition().z > -waterDimensions.z / 2) // if the front is within the bounds
				{
					//float random = ((rand() % 1000)-500) / 1000);
					float depth = surfaceTransform.GetPosition().y - buoyancy.dimensions.y / 2;// location of the bottom of the floaty object
					//cout << depth << endl;
					Vector3 force(0, 0, 0);
					float totalVolume = buoyancy.dimensions.x * buoyancy.dimensions.y * buoyancy.dimensions.z;


					for (int key : buoyancy.HorizontalKeys)
					{
						if (glfwGetKey(getWorld().data.renderUtil->window->glfwWindow, key) == GLFW_PRESS)
						{
							if (buoyancy.currentDensity > buoyancy.liquidDensity * 0.65)
							{
								buoyancy.currentDensity -= buoyancy.liquidDensity * 0.01;
							}
							else
							{
								buoyancy.currentDensity = buoyancy.liquidDensity * 0.65;
							}
						}
						else
						{
							if (buoyancy.currentDensity < buoyancy.liquidDensity)
							{
								buoyancy.currentDensity += buoyancy.liquidDensity * 0.01;
							}
							else
							{
								buoyancy.currentDensity = buoyancy.liquidDensity;
							}
						}
					}

					//out of water
					if (depth >= buoyancy.waterHeight)
					{
						//can adjust the drag component here to be for air
						//cout << " Air " << endl;
						buoyancy.netForce = Lerp(buoyancy.netForce, force, 10 * deltaTime);
					}
					
					// maximum depth
					else if (depth <= buoyancy.waterHeight - buoyancy.dimensions.y && depth + buoyancy.dimensions.y > -waterDimensions.y + buoyancy.waterHeight) // check if the floaty object is fully submerged in the water and not below
					{
						
						if (buoyancy.localOffset.z > 0) //front
						{
							float densityOffset = 0.2 * sin(elapsedTime) + 1;
							force.y += deltaTime * buoyancy.currentDensity * densityOffset * totalVolume;
						}
						else // back
						{
							force.y += deltaTime * buoyancy.currentDensity * totalVolume;
						}
						buoyancy.netForce = Lerp(buoyancy.netForce, force, 10 * deltaTime);
					
					}
					else if (depth + buoyancy.dimensions.y > -waterDimensions.y + buoyancy.waterHeight) // make sure it isnt below (check the top of the buoyancy object vs the bottom of the water)
					{
						
						//partially submerged
						if (buoyancy.localOffset.z > 0) //front
						{
							
							float densityOffset = 0.2 * sin(elapsedTime) + 1;
							//std::cout << "offset: " << densityOffset << std::endl;
							force.y += deltaTime * buoyancy.currentDensity * densityOffset * (buoyancy.waterHeight - depth) * buoyancy.dimensions.x * buoyancy.dimensions.z;
						}
						else // back
						{
							force.y += deltaTime * buoyancy.currentDensity * (buoyancy.waterHeight - depth) * buoyancy.dimensions.x * buoyancy.dimensions.z;
						}

						buoyancy.netForce = Lerp(buoyancy.netForce, force, 10 * deltaTime);
						

					}

					//tried using lerped net force to remove jitter however would cause more *************************************************************
					forceAcc.AddForceAtPoint(force, surfaceTransform.GetPosition(), targetTransform.GetPosition());
					
					//std::cout << "Buoyancy Forces:" << std::endl;
					getWorld().data.renderUtil->DrawLine(worldSurfacePosition, worldSurfacePosition + buoyancy.netForce, Color::Blue);
					//std::cout << "Force: " << force.y << std::endl;
					//std::cout <<  "Net Force: " << buoyancy.netForce.y << std::endl;
					//std::cout << force.x << std::endl;
					//dddstd::cout << force.z << std::endl;
					//std::cout << "Depth: " << depth << std::endl;
				}
				elapsedTime += deltaTime;
				if (elapsedTime > 1000)
				{
					elapsedTime = 0.0f;
				}
			}

			

			

				
		}

	}

	Vector3 BuoyancySystem::Lerp(Vector3 a, Vector3 b, float t)
	{
		return a + (t * (b - a));
	}
	
	
}
