#pragma once
#include "ECSConfig.h"
#include "TrianglePlaneComponent.h"

namespace Reality
{
	class TrianglePlaneCollisionSystem : public ECSSystem
	{
	public:
		TrianglePlaneCollisionSystem();
		void Update(float deltaTime);
	};
}
