#pragma once
#include "ECSConfig.h"
#include "AeroMinMaxComponent.h"
#include "AeroControlComponent.h"

namespace Reality
{
	class AeroControlSystem : public ECSSystem
	{
	public:
		AeroControlSystem();
		void Update(float deltaTime);
	private:
		bool pKey = false;
		bool nKey = false;
	};
}
