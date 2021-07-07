#pragma once
#include "ECSConfig.h"
#include "TriangleOfBridgeComponent.h"

namespace Reality
{
	class TriangleOfBridgeSystem : public ECSSystem
	{
	public:
		TriangleOfBridgeSystem();
		void Update(float deltaTime);

		void SetSphere(ECSEntity _Sphere)
		{
			Sphere = _Sphere;
		}

	private :
		ECSEntity Sphere = -99;
	};
}
