#pragma once
#include "ECSConfig.h"
#include "TransformComponentV2.h"
#include "RigidbodyComponent.h"

namespace Reality
{
	class RigidbodySystem : public ECSSystem
	{
	public:
		RigidbodySystem();
		void Update(float deltaTime);
	};
}
