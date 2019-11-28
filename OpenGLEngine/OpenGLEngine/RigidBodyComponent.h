#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct RigidBodyComponent
	{
		RigidBodyComponent(float mass = 1.0f, float _linearDamping = 0.4f, float _angularDamping = 0.3f, Vector3 _velocity = Vector3(0, 0, 0), Vector3 _angularVelocity = Vector3(0, 0, 0), float _gravityScale = 1)
			: inverseMass(1.0f / mass),  velocity(_velocity), angularVelocity(_angularVelocity), linearDamping(_linearDamping), angularDamping(_angularDamping), gravityScale(_gravityScale), rp3dId(-1)
		{
			inertiaTensor = glm::mat3(0.0f);
			inertiaTensor[0][0] = 0.001f;
			inertiaTensor[1][1] = 0.001f;
			inertiaTensor[2][2] = 0.001f;
			accelaration = Vector3(0, 0, 0);
			angularAccelaration = Vector3(0, 0, 0);
			forceAccumulator = Vector3(0, 0, 0);
			torqueAccumulator = Vector3(0, 0, 0);
		}
		float inverseMass;
		Vector3 velocity;
		Vector3 angularVelocity;
		Vector3 accelaration;
		Vector3 angularAccelaration;
		Mat3 inertiaTensor;
		float gravityScale;
		float linearDamping;
		float angularDamping;
		int rp3dId;

		Mat3 worldInverseInertiaTensor(Mat3 localToWorld)
		{
			Mat3 worldInertiaTensor = localToWorld * inertiaTensor * glm::inverse(localToWorld);
			return glm::inverse(worldInertiaTensor);
		}


		// Forces
		inline void AddForce(Vector3 force)
		{
			forceAccumulator += force;
		}
		inline Vector3 GetForce()
		{
			return forceAccumulator;
		}
		inline void ResetForceAccumulator()
		{
			forceAccumulator = Vector3(0, 0, 0);
		}

		// Torque and force
		inline void AddForceAtPoint(Vector3 force, Vector3 point, Vector3 origin)
		{
			AddForce(force);
			AddTorque(glm::cross(point - origin, force));
		}

		// Torque
		inline void AddTorque(Vector3 torque)
		{
			torqueAccumulator += torque;
		}
		inline Vector3 GetTorque()
		{
			return torqueAccumulator;
		}
		inline void ResetTorqueAccumulator()
		{
			torqueAccumulator = Vector3(0, 0, 0);
		}
	private:
		Vector3 forceAccumulator;
		Vector3 torqueAccumulator;
	};
}
