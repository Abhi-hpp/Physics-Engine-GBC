#pragma once
#include "ECSConfig.h"
#include "AeroComponent.h"
#include "AeroMinMaxComponent.h"

namespace Reality
{
	class SetAerodynamicTensorSystem : public ECSSystem
	{
	public:
		SetAerodynamicTensorSystem();
		void Update(float deltaTime);
	};
}
