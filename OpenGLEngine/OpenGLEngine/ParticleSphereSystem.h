#pragma once
#include "ECSConfig.h"
#include "ParticleSphereComponent.h"
#include "TransformComponent.h"

namespace Reality
{
	class ParticleSphereSystem : public ECSSystem
	{
	public:
		ParticleSphereSystem();
		void Update(float deltaTime);

	private :
		bool CheckCollision(ECSEntity sphereA, ECSEntity sphereB);
	};
}
