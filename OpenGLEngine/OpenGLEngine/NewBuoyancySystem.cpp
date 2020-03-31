#include "NewBuoyancySystem.h"
#include "BuoyancyCenterComponent.h"
#include "RigidBodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	NewBuoyancySystem::NewBuoyancySystem()
	{
		requireComponent<BuoyancyCenterComponent>();
		requireComponent<RigidbodyComponent>();
		requireComponent<ForceAndTorqueAccumulatorComponent>();
		requireComponent<TransformComponentV2>();
	}

	void NewBuoyancySystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& buoy = e.getComponent<BuoyancyCenterComponent>();
			auto& rigidbody = e.getComponent<RigidbodyComponent>();
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& accumulator = e.getComponent<ForceAndTorqueAccumulatorComponent>();

			//Vector3 buoyPosition = transform.GetPosition() + buoy.positionOffset;
			Vector3 buoyPosition = transform.LocalToWorldPosition(buoy.positionOffset);

			if(buoyPosition.y < 0.0f)
			{ 
			float depth = buoyPosition.y;

			Vector3 force = Vector3(0.0f, UpForce(depth, buoy.volume), 0.0f);

			accumulator.AddForceAtPoint(force, buoyPosition, transform.GetPosition());

			getWorld().data.renderUtil->DrawCube(buoyPosition, Vector3(1, 1, 1));
			}
			
		}
	}

	float NewBuoyancySystem::UpForce(float depth, float vol)
	{
		return (liquidDensity * vol * abs(depth) * 0.1f);
	}
}
