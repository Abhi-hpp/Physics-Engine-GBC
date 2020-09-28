#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct ForceAndTorqueAccumulatorComponent
	{
		ForceAndTorqueAccumulatorComponent(float _mass = 1.0f, float _inertia = 1.0f)
			: inverseMass(1.0f / _mass), forceAccumulator(Vector3(0, 0, 0)),
			inertiaTensor(Mat3(_inertia)), torqueAccumulator(Vector3(0, 0, 0))
		{

		}
		float inverseMass;
		Mat3 inertiaTensor;

		inline void AddForce(const Vector3& force)
		{
			forceAccumulator += force;
		}
		inline void ResetForceAccumulator()
		{
			forceAccumulator = Vector3(0, 0, 0);
		}
		inline const Vector3& GetAccumulatedForce()
		{
			return forceAccumulator;
		}

		inline void AddTorque(const Vector3& torque)
		{
			torqueAccumulator += torque;
		}
		inline void ResetTorqueAccumulator()
		{
			torqueAccumulator = Vector3(0, 0, 0);
		}
		inline const Vector3& GetAccumulatedTorque()
		{
			return torqueAccumulator;
		}

		inline void AddForceAtPoint(const Vector3& force, const Vector3& point, const Vector3& origin)
		{
			AddForce(force);
			AddTorque(glm::cross(point - origin, force));
		}

		inline const Mat3& GetWorldInverseInertiaTensor(const Mat3& localToWorldRotation)
		{
			return localToWorldRotation * inertiaTensor * glm::inverse(localToWorldRotation);
		}

	private:
		Vector3 forceAccumulator;
		Vector3 torqueAccumulator;
	};
}
