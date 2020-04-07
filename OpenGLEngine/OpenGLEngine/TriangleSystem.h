#pragma once
#include "ECSConfig.h"
#include "TriangleComponent.h"
#include "TransformComponent.h"
#include "ParticleSphereComponent.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	class TriangleSystem : public ECSSystem
	{
	public:
		TriangleSystem();
		void Update(float deltaTime);
	};
}
