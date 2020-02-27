#pragma once
#include "ECSConfig.h"
#include "ParticleSphereComponent.h"
#include "TransformComponent.h"
#include "PlaneComponent.h"

namespace Reality
{
	class ParticleSphereSystem : public ECSSystem
	{
	public:
		ParticleSphereSystem();
		void Update(float deltaTime);
	private:
		bool createBox = false;
		ECSEntity boundingBox;
		void CheckCollision(ECSEntity sphereEntityA, ECSEntity sphereEntityB);
		bool IsInsidePlane1(Vector3 position, PlaneComponent plane);
		bool IsInsidePlane2(Vector3 position, PlaneComponent plane);
		void CheckCollisionWithPlane(ECSEntity sphereEntityA, ECSEntity plane);
	};
}
