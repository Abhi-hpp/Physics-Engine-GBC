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

	private:
		bool CheckIntersection(Vector3 A, Vector3 B, Vector3 C, Vector3 P);
	};
}
