#pragma once
#include "ECSConfig.h"
#include "ContactEvent.h"
#include <React3D/reactphysics3d.h>

namespace Reality
{
	class ContactResolutionSystem : public ECSSystem
	{
	public:
		ContactResolutionSystem(rp3d::CollisionWorld& _rp3dWorld);
		void Update(float deltaTime);
		rp3d::CollisionWorld& rp3dWorld;
		float angularLimitConstant = 0.2f;
	private:
		void ResolvePenetration(ContactEvent& contact);
		void ResolveVelocity(ContactEvent& contact);
		void CalculateContactBasis(Vector3 contactNormal, Mat3& transformationMat, Vector3& y, Vector3& z);
	};	
}