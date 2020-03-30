#pragma once
#include "ECSConfig.h"
#include "WindComponent.h"

namespace Reality
{
	class WindSystem : public ECSSystem
	{
	public:
		WindSystem();
		void Update(float deltaTime);
	};
}
