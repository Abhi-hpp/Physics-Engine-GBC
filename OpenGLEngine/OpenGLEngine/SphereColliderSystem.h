#pragma once
#include "ECSConfig.h"
#include "SphereColliderComponent.h"
#include "RigidbodyComponent.h"
#include <React3D/reactphysics3d.h>

namespace Reality
{
	class SphereColliderSystem : public ECSSystem
	{
	public:
		SphereColliderSystem(rp3d::CollisionWorld& _rp3dWorld);
		void Update(float deltaTime);
	private:
		rp3d::CollisionWorld& rp3dWorld;
	};
}
