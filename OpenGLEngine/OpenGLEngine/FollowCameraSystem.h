#pragma once
#include "ECSConfig.h"
#include "FollowCameraComponent.h"
#include "TransformComponentV2.h"

namespace Reality
{
	class FollowCameraSystem : public ECSSystem
	{
	public:
		FollowCameraSystem();
		void Update(float deltaTime);
	};
}
