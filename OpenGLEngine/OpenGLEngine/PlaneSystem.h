#pragma once
#include "ECSConfig.h"
#include "PlaneComponent.h"
#include "ParticleSphereComponent.h"

namespace Reality
{
	class PlaneSystem : public ECSSystem
	{
	public:
		PlaneSystem();
		void Update(float deltaTime);

	private:
		void checkCollision(ECSEntity plane, ECSEntity sphere);
		bool checkSameSide(Vector3 p1, Vector3 p2, Vector3 a, Vector3 b);
		bool checkPointInTriangle(Vector3 p1, Vector3 a, Vector3 b, Vector3 c);
	};
}
