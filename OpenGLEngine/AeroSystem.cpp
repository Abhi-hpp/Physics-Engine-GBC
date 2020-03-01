#include "AeroSystem.h"
#include "RigidBodyComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	AeroSystem::AeroSystem()
	{
		requireComponent<AeroComponent>();
	}

	void AeroSystem::UpdateForceFromTensor(ECSWorld& world, AeroComponent& aero, RigidBodyComponent& body, TransformComponentV2& transform)
	{
		// Calculate total velocity (windspeed and body's velocity).
		Vector3 velocity = body.velocity;
		velocity += windspeed;

		// Calculate the velocity in body coordinates
		Vector3 bodyVel = transform.WorldToLocalDirection(velocity);

		// Calculate the force in body coordinates
		Vector3 bodyForce = aero.aerodynamicTensor * bodyVel /  1.0f;
		Vector3 force =  transform.LocalToWorldDirection(bodyForce);

		// Apply the force
		Vector3 forcePoint = transform.LocalToWorldPosition(aero.relativePoint);
		body.AddForceAtPoint(force, forcePoint, transform.GetPosition());

		//world.data.renderUtil->DrawLine(transform.GetPosition(), forcePoint + force * 1000.0f, Color::Purple);
		world.data.renderUtil->DrawLine(forcePoint, forcePoint + force * 1000.0f, Color::Purple);
	}

	void AeroSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			auto& aero = e.getComponent<AeroComponent>();
			if (aero.target.hasComponent<RigidBodyComponent>() && aero.target.hasComponent<TransformComponentV2>())
			{
				auto& rigidbody = aero.target.getComponent<RigidBodyComponent>();
				auto& transform = aero.target.getComponent<TransformComponentV2>();
				UpdateForceFromTensor(getWorld(), aero, rigidbody, transform);
			}
		}
	}
}
