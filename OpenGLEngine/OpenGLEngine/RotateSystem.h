#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "RotateComponent.h"

using namespace Reality;
class RotateSystem : public ECSSystem
{
<<<<<<< Updated upstream
public:
	RotateSystem();
	void Update(float deltaTime);
};

=======
	class RotateSystem : public ECSSystem
	{
	public:
		RotateSystem();
		void Update(float deltaTime);
	private:
		float timer = 0;
	};
}
>>>>>>> Stashed changes
