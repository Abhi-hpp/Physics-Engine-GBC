#pragma once
#include "ECSConfig.h"
#include "MoveInBoundsComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class MoveInBoundsSystem : public ECSSystem
	{
	public:
		MoveInBoundsSystem();
		void Update(float deltaTime);
	};
}
