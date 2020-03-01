#pragma once
#include "ECSConfig.h"
#include "PairedSpringComponent.h"

namespace Reality
{
	class PairedSpringForceGeneratorSystem : public ECSSystem
	{
	public:
		PairedSpringForceGeneratorSystem();
		void Update(float deltaTime);
	};
}

