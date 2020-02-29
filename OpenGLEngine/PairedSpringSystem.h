#pragma once
#include "ECSConfig.h"
#include "PairedSpringComponent.h"

namespace Reality
{
	class PairedSpringSystem : public ECSSystem
	{
	public:
		PairedSpringSystem();
		void Update(float deltaTime);
	};
}
