#include "ContactResolutionSystem.h"

namespace Reality
{
	ContactResolutionSystem::ContactResolutionSystem(rp3d::CollisionWorld& _rp3dWorld)
		:rp3dWorld(_rp3dWorld)
	{
		collisionCallback = new RP3DCollisionCallback(getWorld());
		rp3dWorld.testCollision(collisionCallback);
	}

	void ContactResolutionSystem::Update(float deltaTime)
	{
		for (auto e : getEntities())
		{
			
		}
	}
}
