#pragma once
#include "ECSConfig.h"
#include "PlaneComponent.h"

namespace Reality
{
	class PlaneSystem : public ECSSystem
	{
	public:
		PlaneSystem();
		void Update(float deltaTime);
	private:
		float Area(Vector3, Vector3, Vector3);
	};
}
