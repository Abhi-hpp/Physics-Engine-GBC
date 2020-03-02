#pragma once
#include "ECSConfig.h"
#include "PairedBungeeChordComponent.h"

namespace Reality
{
	class PairedBungeeChordSystem : public ECSSystem
	{
	public:
		PairedBungeeChordSystem();
		void Update(float deltaTime);
	};
}
