#include "NewBuoyancy3System.h"
#include "BuoyancyCenter3Component.h"
#include "RigidBodyComponent.h"
#include "ForceAndTorqueAccumulatorComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	NewBuoyancy3System::NewBuoyancy3System()
	{
		requireComponent<BuoyancyCenter3Component>();
		requireComponent<RigidbodyComponent>();
		requireComponent<ForceAndTorqueAccumulatorComponent>();
		requireComponent<TransformComponentV2>();
	}

	void NewBuoyancy3System::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& buoy = e.getComponent<BuoyancyCenter3Component>();
			auto& rigidbody = e.getComponent<RigidbodyComponent>();
			auto& transform = e.getComponent<TransformComponentV2>();
			auto& accumulator = e.getComponent<ForceAndTorqueAccumulatorComponent>();

			Vector3 buoyPosition = transform.LocalToWorldPosition(buoy.positionOffset);

			Vector3 offset = buoy.positionOffset;

			float pitch = transform.GetEulerAngles().x;

			float length = buoy.positionOffset.length();




			if (buoyPosition.y < 0.0f)
			{
				float depth = buoyPosition.y;

				Vector3 force = Vector3(0.0f, UpForce(depth, buoy.volume), 0.0f);

				accumulator.AddForceAtPoint(force, buoyPosition, transform.GetPosition());

				getWorld().data.renderUtil->DrawCube(buoyPosition, Vector3(1, 1, 1));
			}
		}
	}

	float NewBuoyancy3System::UpForce(float depth, float vol)
	{
		return (liquidDensity * vol * abs(depth) * 0.1f);
	}
}
