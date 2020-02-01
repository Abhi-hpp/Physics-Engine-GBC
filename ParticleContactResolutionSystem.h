#pragma once
#include "ECSConfig.h"
#include "ParticleContactEvent.h"

namespace Reality
{
	class ParticleContactResolutionSystem : public ECSSystem
	{
	public:
		ParticleContactResolutionSystem();
		void Update(float deltaTime);
	private :
		float CalculateSeparatingVelociy(ParticleContactEvent& contact);
		void ResolveVelocity(ParticleContactEvent& contact, float deltaTime);
	};
}
