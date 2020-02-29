#pragma once
#include "ECSConfig.h"
#include "CameraLookComponent.h"

namespace Reality
{
	class CameraLookSystem : public ECSSystem
	{
	public:
		CameraLookSystem();
		void Update(float deltaTime);
	};
}
