#pragma once
#include "ECSConfig.h"
#include "TransformComponent.h"
#include "ParticleSphereComponent.h"

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
	};
}
