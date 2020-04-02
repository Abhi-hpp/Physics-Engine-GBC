#pragma once
#include "ECSConfig.h"
#include "RigidbodyComponent.h"

namespace Reality
{
	struct ContactEvent
	{
		ContactEvent(ECSEntity _bodyA =  ECSEntity(), ECSEntity _bodyB =  ECSEntity(), Vector3 _normal = Vector3(0, 0 , 0), float _penetrationDepth = 0, Vector3 _localPointOnShape1 = Vector3(0, 0, 0), Vector3 _localPointOnShape2 = Vector3(0, 0, 0), Vector3 _worldPoint1 = Vector3(0, 0, 0), Vector3 _worldPoint2 = Vector3(0, 0, 0), float _restitution = 1.0f)
			:entityA(_bodyA), entityB(_bodyB), normal(_normal), penetrationDepth(_penetrationDepth), localPointOnShape1(_localPointOnShape1), localPointOnShape2(_localPointOnShape2), worldPoint1(_worldPoint1), worldPoint2(_worldPoint2), restitution(_restitution)
		{

		}

		ECSEntity entityA;

		ECSEntity entityB;

		/// Normalized normal vector of the contact (from body1 toward body2) in world space
		Vector3 normal;

		/// Penetration depth
		float penetrationDepth;

		/// Contact point on proxy shape 1 in local-space of proxy shape 1
		Vector3 localPointOnShape1;

		/// Contact point on proxy shape 2 in local-space of proxy shape 2
		Vector3 localPointOnShape2;

		/// Contact point on proxy shape 1 in world-space
		Vector3 worldPoint1;

		/// Contact point on proxy shape 2 in world-space
		Vector3 worldPoint2;

		/// Coefficient Of restitution
		float restitution;
	};
}
