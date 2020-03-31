#include "BuoyancySystem.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "ParticleComponent.h"
#include "RigidBodyComponent.h"
namespace Reality
{
	BuoyancySystem::BuoyancySystem()
	{
		requireComponent<BuoyancyComponent>();
		requireComponent<TransformComponentV2>();
		//requireComponent<ForceAndTorqueAccumulatorComponent>();
	}
	Vector3 waterVolume = Vector3(30000, 5000, 30000);
	
	void BuoyancySystem::Update(float deltaTime)
	{
		getWorld().data.renderUtil->DrawCube(Vector3(0, 0, 0),
			waterVolume,
			Vector3(0, 0, 0), Color::Blue);

		for (auto e : getEntities())
		{
			//Vector3 position = e.getComponent<TransformComponentV2>().GetPosition();

			auto& buoyantObjTrans = e.getComponent <TransformComponentV2>();
			auto& buoyant = e.getComponent<BuoyancyComponent>();
			if (buoyant.targetEntity.hasComponent<TransformComponentV2>() &&
				buoyant.targetEntity.hasComponent<RigidbodyComponent>() &&
				buoyant.targetEntity.hasComponent<ForceAndTorqueAccumulatorComponent>()
				)
			{
				auto& targetTransform = buoyant.targetEntity.getComponent<TransformComponentV2>();
				auto& rigidbody = buoyant.targetEntity.getComponent<RigidbodyComponent>();
				auto& forceAcc = buoyant.targetEntity.getComponent<ForceAndTorqueAccumulatorComponent>();

				Vector3 worldSurfacePosition = targetTransform.LocalToWorldPosition(buoyant.localOffset);
				buoyantObjTrans.SetPosition(worldSurfacePosition);
				buoyantObjTrans.SetOrientation(targetTransform.GetOrientation());
				getWorld().data.renderUtil->DrawCube(buoyantObjTrans.GetPosition(),
					Vector3(1, 1, 1),
					buoyantObjTrans.GetOrientation(), Color::Green);

				if ((buoyantObjTrans.GetPosition().x > -waterVolume.x * 0.5 && buoyantObjTrans.GetPosition().x < waterVolume.x * 0.5)
					&& (buoyantObjTrans.GetPosition().y > -waterVolume.y * 0.5 && buoyantObjTrans.GetPosition().y < waterVolume.y * 0.5)
					&& (buoyantObjTrans.GetPosition().z > -waterVolume.z * 0.5 && buoyantObjTrans.GetPosition().z < waterVolume.z * 0.5))
				{
					

					Vector3 force(0, 0.1f, 0);
					float depth = abs(buoyantObjTrans.GetPosition().y - waterVolume.y * 0.5);
						if (depth >= buoyant.maxDepth)
						{
							force.y = buoyant.density * buoyant.volume.x * buoyant.volume.y * buoyant.volume.z;
						}
						else
						{
							float depthRatio = depth / buoyant.maxDepth;
							force.y = buoyant.density * buoyant.volume.x * buoyant.volume.y * buoyant.volume.z * depthRatio;

						}
					forceAcc.AddForceAtPoint(force, buoyantObjTrans.GetPosition(), targetTransform.GetPosition());

					getWorld().data.renderUtil->DrawLine(buoyantObjTrans.GetPosition(), buoyantObjTrans.GetPosition() + force, Color::Red);

				}
			}
				
				
			
				
			
		} 
	}
	
}
