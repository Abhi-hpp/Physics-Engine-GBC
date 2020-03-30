#pragma once
#include "ECSConfig.h"

namespace Reality
{
	struct FollowCameraComponent
	{
		FollowCameraComponent(Vector3 _follow = Vector3(0.0f, 100.0f, 0.0f))
			:follow(_follow)
		{

		}
		Vector3 follow;
	};
}