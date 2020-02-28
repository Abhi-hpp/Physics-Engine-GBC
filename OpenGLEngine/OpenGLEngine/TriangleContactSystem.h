#pragma once
#include "ECSConfig.h"
#include "TriangleComponent.h"

namespace Reality
{
	class TriangleContactSystem : public ECSSystem
	{
	public:
		TriangleContactSystem();
		void Update(float deltaTime);

		void CreateSphere(ECSEntity _sphere)
		{
			sphere = _sphere;
		}

		bool sphereCreated = false;

	private:
		ECSEntity sphere;
	};
}