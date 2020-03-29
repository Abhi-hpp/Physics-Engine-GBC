#pragma once
#include "ECSConfig.h"
#include "ContactInfoReciever.h"
#include <React3D/reactphysics3d.h>

namespace Reality
{
	class ContactGenerationSystem : public ECSSystem
	{
	public:
		ContactGenerationSystem(rp3d::CollisionWorld& _rp3dWorld);
		void Update(float deltaTime);
		~ContactGenerationSystem();
	private:
		rp3d::CollisionWorld& rp3dWorld;
		ContactInfoReciever* contactReciever = nullptr;
	};
}
