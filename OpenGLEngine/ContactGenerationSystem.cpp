#include "ContactGenerationSystem.h"

namespace Reality
{
	ContactGenerationSystem::ContactGenerationSystem(rp3d::CollisionWorld& _rp3dWorld) : rp3dWorld(_rp3dWorld)
	{
		
	}

	void ContactGenerationSystem::Update(float deltaTime)
	{
		if (contactReciever == nullptr)
		{
			contactReciever = new ContactInfoReciever(getWorld());
		}
		rp3dWorld.testCollision(contactReciever);
	}

	ContactGenerationSystem::~ContactGenerationSystem()
	{
		delete contactReciever;
	}
}
