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
		bool SameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b);
		bool PointInTriangle(Vector3 p, Vector3 a, Vector3 b, Vector3 c);
	};
}
