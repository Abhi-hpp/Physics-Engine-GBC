#pragma once
#include "ECSConfig.h"
#include "BridgeComponent.h"

namespace Reality
{
	class BridgeSystem : public ECSSystem
	{
	private:
		ECSEntity Sphere = -99;
	public:
		BridgeSystem();
		void Update(float deltaTime);

		void SetSphere(ECSEntity _Sphere)
		{
			Sphere = _Sphere;
		}
	};
}
