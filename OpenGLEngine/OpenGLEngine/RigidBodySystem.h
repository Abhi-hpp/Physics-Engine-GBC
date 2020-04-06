#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "RigidbodyComponent.h"
#include <React3D/reactphysics3d.h>

namespace Reality
{
	class RigidbodySystem : public ECSSystem
	{
	public:
		RigidbodySystem(rp3d::CollisionWorld& _rp3dWorld);
		void Update(float deltaTime);
	private:
		rp3d::CollisionWorld& rp3dWorld;
	};
}
