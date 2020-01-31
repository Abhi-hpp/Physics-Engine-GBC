#include "BuoyancyForceSystem.h"
#include "ForceAccumulatorComponent.h"

namespace Reality
{
	BuoyancyForceSystem::BuoyancyForceSystem()
	{
		requireComponent<TransformComponent>();
		requireComponent<BuoyancyComponent>();
		requireComponent<ForceAccumulatorComponent>();
	}

	Vector3 waterVolume = Vector3(200, 200, 200);
	float BuoyancyForceSystem::liquidDensity = 40.0f;

	void BuoyancyForceSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			Vector3 position = e.getComponent<TransformComponent>().position;

			if ((position.x > -waterVolume.x * 0.5 && position.x < waterVolume.x * 0.5)		
				&& 	(position.y > -waterVolume.y * 0.5 && position.y < waterVolume.y * 0.5) 
				&&  (position.z > -waterVolume.z * 0.5 && position.z < waterVolume.z * 0.5))
			{
				auto& buoyant = e.getComponent<BuoyancyComponent>();
				auto& buoyantTransform = e.getComponent<TransformComponent>();
				auto& forceAcc = e.getComponent<ForceAccumulatorComponent>();


				Vector3 force(0, 1, 0);

				float depth = abs(buoyantTransform.position.y - waterVolume.y * 0.5);
				
				if(depth >= buoyant.maxDepth)
				{
					force.y = liquidDensity * buoyant.volume;	
				}
				else
				{
					float depthRatio = depth / buoyant.maxDepth;

					force.y = liquidDensity * depthRatio * buoyant.volume;
				}

				forceAcc.AddForce(force);
			}

		}
		getWorld().data.renderUtil->DrawCube(Vector3(0, 0, 0), Vector3(200, 200, 200), Vector3(0,0,0), Color::Blue);
	}
}
