#pragma once
#include "ECSConfig.h"
<<<<<<< Updated upstream
#include "LifeTimeComponent.h"
#include "TransformComponentV2.h"
=======
#include "TransformComponentV2.h"
#include "LifeTimeComponent.h"
>>>>>>> Stashed changes

namespace Reality
{
	class LifeTimeSystem : public ECSSystem
	{
	public:
		LifeTimeSystem();
		void Update(float deltaTime);
	};
}
