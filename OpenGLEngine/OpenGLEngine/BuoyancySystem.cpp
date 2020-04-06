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

			if (buoyancy.targetEntity.hasComponent<TransformComponentV2>() && buoyancy.targetEntity.hasComponent<RigidbodyComponent>() && buoyancy.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>())
			{
				auto& targetTransform = buoyancy.targetEntity.getComponent<TransformComponentV2>();
				auto& rigidbody = buoyancy.targetEntity.getComponent<RigidbodyComponent>();
				auto& forceAcc = buoyancy.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				Vector3 worldSurfacePosition = targetTransform.LocalToWorldPosition(buoyancy.localOffset);
				surfaceTransform.SetPosition(worldSurfacePosition);
				surfaceTransform.SetOrientation(targetTransform.GetOrientation());

				float deltaDensity = (buoyancy.liquidDensity - 800) / 700;

				float g = deltaDensity;
				float r = 1 - g;

				Color col = Color(0, 1, 0, 1);

				getWorld().data.renderUtil->DrawCube(Vector3(0.0f, -waterDimensions.y / 2 + buoyancy.waterHeight, 0.0f), waterDimensions, Vector3(0, 0, 0), col);

				if (surfaceTransform.GetPosition().x < waterDimensions.x / 2 && surfaceTransform.GetPosition().x > -waterDimensions.x / 2 
					&& surfaceTransform.GetPosition().z < waterDimensions.z / 2 && surfaceTransform.GetPosition().z > -waterDimensions.z / 2) 
				{
					float depth = surfaceTransform.GetPosition().y - buoyancy.dimensions.y / 2;
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

					if (depth >= buoyancy.waterHeight)
					{
						buoyancy.netForce = Lerp(buoyancy.netForce, force, 10 * deltaTime);
					}

					else if (depth <= buoyancy.waterHeight - buoyancy.dimensions.y && depth + buoyancy.dimensions.y > -waterDimensions.y + buoyancy.waterHeight) // check if the floaty object is fully submerged in the water and not below
					{
						if (buoyancy.localOffset.z > 0) 
						{
							float densityOffset = 0.2 * sin(elapsedTime) + 1;
							force.y += deltaTime * buoyancy.currentDensity * densityOffset * totalVolume;
						}
						else
						{
							force.y += deltaTime * buoyancy.currentDensity * totalVolume;
						}

						buoyancy.netForce = Lerp(buoyancy.netForce, force, 10 * deltaTime);

					}
					else if (depth + buoyancy.dimensions.y > -waterDimensions.y + buoyancy.waterHeight)
					{
						if (buoyancy.localOffset.z > 0)
						{
							float densityOffset = 0.2 * sin(elapsedTime) + 1;
							force.y += deltaTime * buoyancy.currentDensity * densityOffset * (buoyancy.waterHeight - depth) * buoyancy.dimensions.x * buoyancy.dimensions.z;
						}
						else
						{
							force.y += deltaTime * buoyancy.currentDensity * (buoyancy.waterHeight - depth) * buoyancy.dimensions.x * buoyancy.dimensions.z;
						}

						buoyancy.netForce = Lerp(buoyancy.netForce, force, 10 * deltaTime);
					}
					forceAcc.AddForceAtPoint(force, surfaceTransform.GetPosition(), targetTransform.GetPosition());

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
