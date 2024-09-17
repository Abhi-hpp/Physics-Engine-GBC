#pragma once
#include "ECSConfig.h"
#include "TriangleComponent.h"

namespace Reality
{
	class TriangleSystem : public ECSSystem
	{
	private:
		ECSEntity Sphere = -99;
	public:
		TriangleSystem();
		void Update(float deltaTime);

		void SetSphere(ECSEntity _Sphere)
		{
			Sphere = _Sphere;
		}
	};
}
