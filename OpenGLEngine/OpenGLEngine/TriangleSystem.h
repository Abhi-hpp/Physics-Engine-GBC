#pragma once
#include "ECSConfig.h"
#include "TriangleComponent.h"

namespace Reality
{
	class TriangleSystem : public ECSSystem
	{
	public:
		TriangleSystem();
		void Update(float deltaTime);

		void SetSphere(ECSEntity _sphere)
		{
			sphere = _sphere;
		}

	private:
		ECSEntity sphere = 0;
	};
}
