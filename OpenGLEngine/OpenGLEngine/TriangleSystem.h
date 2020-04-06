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
		void CheckCollision(ECSEntity PlaneEntity, ECSEntity sphereEntity);
	};
}
