#pragma once
#include "ECSConfig.h"
<<<<<<< Updated upstream
#include "AeroMinMaxComponent.h"
=======
#include "AeroSurfaceComponent.h"
>>>>>>> Stashed changes
#include "AeroControlComponent.h"

namespace Reality
{
	class AeroControlSystem : public ECSSystem
	{
	public:
		AeroControlSystem();
		void Update(float deltaTime);
<<<<<<< Updated upstream
	private:
		bool pKey = false;
		bool nKey = false;
=======
>>>>>>> Stashed changes
	};
}
