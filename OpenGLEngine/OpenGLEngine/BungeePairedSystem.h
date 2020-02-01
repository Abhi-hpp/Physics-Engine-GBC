#pragma once
#include "ECSConfig.h"
#include "BungeePairedComponent.h"

namespace Reality
{
	class BungeePairedSystem : public ECSSystem
	{
	public:
		BungeePairedSystem();
		void Update(float deltaTime);
	};
}
