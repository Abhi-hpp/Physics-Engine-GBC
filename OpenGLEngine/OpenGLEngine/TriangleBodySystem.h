#pragma once
#include "ECSConfig.h"
#include "TriangleBodyComponent.h"

namespace Reality
{
	class TriangleBodySystem : public ECSSystem
	{
	public:
		TriangleBodySystem();
		bool CheckIntersection(Vector3 A, Vector3 B, Vector3 C, Vector3 P);
		void Update(float deltaTime);
	};
}
