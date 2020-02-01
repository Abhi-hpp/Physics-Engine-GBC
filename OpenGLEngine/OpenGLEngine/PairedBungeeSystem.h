#pragma once
#include "ECSConfig.h"
#include "PairedBungeeComponent.h"

namespace Reality
{
	class PairedBungeeSystem : public ECSSystem
	{
	public:
		PairedBungeeSystem();
		void Update(float deltaTime);
	};
}
